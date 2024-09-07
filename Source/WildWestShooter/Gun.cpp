#include "Gun.h"
#include "DrawDebugHelpers.h"
#include "WildWestShooterPlayer.h"


AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = false;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger() {
	// TODO: muzzle flash particles
	// TODO: gun sound

	FHitResult Hit;
	FVector ShotDirection; 

	bool bSuccess = GunTrace(Hit, ShotDirection);

	if(bSuccess){
		DrawDebugPoint(GetWorld(), Hit.Location, 5, FColor::Blue, true);
		AActor* HitActor = Hit.GetActor();
		
		if(HitActor){
			UE_LOG(LogTemp, Warning, TEXT("hit actor with name: %s"), *HitActor->GetActorNameOrLabel());
			AWildWestShooterPlayer* HitPlayer = Cast<AWildWestShooterPlayer>(HitActor);
			if(HitPlayer){
				UE_LOG(LogTemp, Warning, TEXT("hit bone with name: %s"), *Hit.BoneName.ToString());
				HitPlayer->HandlePlayerGotShot(ShotDirection * 5000, Hit.Location, Hit.BoneName);
			}
		}
	}
}

bool AGun::GunTrace(FHitResult& OutHit, FVector& OutShotDirection) {
	if(Mesh){
		FTransform MuzzleTransform = Mesh->GetSocketTransform(TEXT("MuzzleFlash"));
		FVector MuzzleLocation = MuzzleTransform.GetLocation();
		FVector EndShotLocation = MuzzleLocation + MuzzleTransform.GetRotation().Vector() * FireRange;
		OutShotDirection = MuzzleTransform.GetRotation().Vector(); // not sure why negative

		// DrawDebugSphere(GetWorld(), MuzzleLocation, 5.f, 8, FColor::Red, true, 5.f);
		DrawDebugLine(GetWorld(), MuzzleLocation, EndShotLocation, FColor::Green, true, 5.f);

		// ignore the gun and the owner of the gun
		FCollisionQueryParams Params;
		Params.AddIgnoredActor(this);
		Params.AddIgnoredActor(GetOwner());

		return GetWorld()->LineTraceSingleByChannel(OutHit, MuzzleLocation, EndShotLocation, ECollisionChannel::ECC_GameTraceChannel1, Params);
	}

	UE_LOG(LogTemp, Error, TEXT("Mesh not assigned!"));
	return false;
}