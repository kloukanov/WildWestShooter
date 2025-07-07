
#include "WildWestShooterPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Gun.h"
#include "PhysicsEngine/PhysicalAnimationComponent.h"

AWildWestShooterPlayer::AWildWestShooterPlayer()
{
	// PrimaryActorTick.bCanEverTick = false;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	PhysicalAnimComp = CreateDefaultSubobject<UPhysicalAnimationComponent>(TEXT("PhysicalAnimationComponent"));
	PhysicalAnimComp->SetSkeletalMeshComponent(GetMesh()); 

	GunHolderComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GunHolderComponent"));
	GunHolderComponent->SetupAttachment(GetMesh(), TEXT("gun_holder"));
}

void AWildWestShooterPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWildWestShooterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UE_LOG(LogTemp, Warning, TEXT("reaction time: %f"), HitReactionTime);

	HitReactionTime = FMath::FInterpTo(HitReactionTime, 0, 0, 10000) - (DeltaTime * 0.1);

	if(HitReactionTime <= 0){
		HitReactionTime = 0;
		GetMesh()->SetAllBodiesBelowSimulatePhysics(FName("pelvis"), false, false);
		SetActorTickEnabled(false);
	}else {
		GetMesh()->SetAllBodiesBelowPhysicsBlendWeight(FName("pelvis"), FMath::Min(HitReactionTime, 1), false, true);
	}
}

void AWildWestShooterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController())) {
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer())) {
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveArmAction, ETriggerEvent::Triggered, this, &AWildWestShooterPlayer::MoveArm);
		EnhancedInputComponent->BindAction(MoveBodyAction, ETriggerEvent::Triggered, this, &AWildWestShooterPlayer::MoveBody);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AWildWestShooterPlayer::Shoot);
		EnhancedInputComponent->BindAction(PickUpGunAction, ETriggerEvent::Triggered, this, &AWildWestShooterPlayer::PickUpGun);
	}
}

void AWildWestShooterPlayer::MoveArm(const FInputActionValue& Value) {
	LookAxisVector += Value.Get<FVector2D>();
}

void AWildWestShooterPlayer::MoveBody(const FInputActionValue& Value) {
	MoveAxisVector += Value.Get<FVector2D>();
	// clamped to values set inside of the animation blend
	MoveAxisVector.X = FMath::Clamp(MoveAxisVector.X, -50.f, 50.f);
	UE_LOG(LogTemp, Warning, TEXT("moveAxisVector: %s"), *MoveAxisVector.ToString());
}

FVector2D AWildWestShooterPlayer::GetLookAxisVector() {
	return LookAxisVector;
}

FVector2D AWildWestShooterPlayer::GetMoveAxisVector() {
	return MoveAxisVector;
}

void AWildWestShooterPlayer::Shoot() {
	if(Gun){
		Gun->PullTrigger();
	}
}

void AWildWestShooterPlayer::PickUpGun() {
	if(Gun){
		// we already have a gun
		return;
	}	
	if(CanGetGun()) {
		GunHolderComponent->SetHiddenInGame(true);
		Gun = GetWorld()->SpawnActor<AGun>(GunClass);
		Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("hand_rWeapon"));
		Gun->SetOwner(this);
	}
}

bool AWildWestShooterPlayer::CanGetGun() {
	FVector GunHolderLocation = GunHolderComponent->GetComponentLocation();
	FVector HandLocation = GetMesh()->GetSocketLocation(TEXT("hand_rWeapon"));

	if(GunHolderLocation.Distance(HandLocation, GunHolderLocation) <= GunPickUpRange) {
		return true;
	}
	return false;
}

void AWildWestShooterPlayer::SetIsDead(bool bDead) {
	IsDead = bDead;
} 

bool AWildWestShooterPlayer::GetIsDead() const {
	return IsDead;
}

void AWildWestShooterPlayer::HandlePlayerGotShot(FVector ShotDirection, FVector Location, FName Bone) {

	if(IsDead){
		GetMesh()->AddImpulseAtLocation(ShotDirection, Location, Bone);
		return;
	}

	// TODO: check health too
	if(Bone.ToString().Equals("head")){
		GetMesh()->SetSimulatePhysics(true);
		GetMesh()->AddImpulseAtLocation(ShotDirection, Location, Bone);
		SetActorTickEnabled(false);
		SetIsDead(true);
		return;
	}

	SetActorTickEnabled(true);
	HitReactionTime += 0.2;

	PhysicalAnimComp->ApplyPhysicalAnimationProfileBelow(TEXT("pelvis"), FName("Hit"), false);
	GetMesh()->SetAllBodiesBelowSimulatePhysics(TEXT("pelvis"), true, false);
	GetMesh()->AddImpulseAtLocation(ShotDirection, Location, Bone);
}