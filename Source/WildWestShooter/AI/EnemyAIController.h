#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

UCLASS()
class WILDWESTSHOOTER_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()
	
protected: 

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* AIBehavior;


public:

	void EnableAI();

	void DisableAI();
};
