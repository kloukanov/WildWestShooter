#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class WILDWESTSHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, Category = "Gun Properties", meta = (AllowPrivateAccess = "true"))
	float FireRange;

public:	
	AGun();

	void PullTrigger();

protected:
	virtual void BeginPlay() override;

	bool GunTrace(FHitResult& OutHit, FVector& OutShotDirection);

public:	
	virtual void Tick(float DeltaTime) override;

};
