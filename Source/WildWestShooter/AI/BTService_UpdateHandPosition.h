#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateHandPosition.generated.h"

UCLASS()
class WILDWESTSHOOTER_API UBTService_UpdateHandPosition : public UBTService_BlackboardBase
{
	GENERATED_BODY()

private:

	class AWildWestShooterPlayer *ShooterAI;

public:
	UBTService_UpdateHandPosition();

protected:
	virtual void OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
