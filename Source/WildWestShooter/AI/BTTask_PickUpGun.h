#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PickUpGun.generated.h"

UCLASS()
class WILDWESTSHOOTER_API UBTTask_PickUpGun : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_PickUpGun();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
