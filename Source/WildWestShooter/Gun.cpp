#include "Gun.h"
#include "DrawDebugHelpers.h"


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
	UE_LOG(LogTemp, Warning, TEXT("pulled trigger"));

	if(Mesh){
		FTransform MuzzleTransform = Mesh->GetSocketTransform(TEXT("MuzzleFlash"));
		FVector MuzzleLocation = MuzzleTransform.GetLocation();
		DrawDebugSphere(GetWorld(), MuzzleLocation, 5.f, 8, FColor::Red, true, 5.f);
	}
	
}