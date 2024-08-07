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
	FVector2D LookAxisVector;

public:

	AWildWestShooterPlayer();

	UFUNCTION(Blueprintcallable)
	FVector2D GetLookAxisVector();

protected:

	virtual void BeginPlay() override;

	void MoveArm(const struct FInputActionValue& Value);

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
