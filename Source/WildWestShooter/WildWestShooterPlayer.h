#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WildWestShooterPlayer.generated.h"

UCLASS()
class WILDWESTSHOOTER_API AWildWestShooterPlayer : public ACharacter
{
	GENERATED_BODY()

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveArmAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* ShootAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PickUpGunAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveBodyAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FVector2D MoveAxisVector;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	FVector2D LookAxisVector;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class AGun> GunClass;

	UPROPERTY()
	class AGun* Gun;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* GunHolderComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gun, meta = (AllowPrivateAccess = "true"))
	float GunPickUpRange;

	class UPhysicalAnimationComponent* PhysicalAnimComp;

	float HitReactionTime = 0;

	bool IsDead = false;

public:

	AWildWestShooterPlayer();

	UFUNCTION(Blueprintcallable)
	FVector2D GetLookAxisVector();

	UFUNCTION(Blueprintcallable)
	FVector2D GetMoveAxisVector();

	void HandlePlayerGotShot(FVector ShotDirection, FVector Location, FName Bone);

	void SetIsDead(bool bDead);

	bool GetIsDead() const;

protected:

	virtual void BeginPlay() override;

	void MoveArm(const struct FInputActionValue& Value);

	void MoveBody(const struct FInputActionValue& Value);

	void Shoot();

	void PickUpGun();

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
