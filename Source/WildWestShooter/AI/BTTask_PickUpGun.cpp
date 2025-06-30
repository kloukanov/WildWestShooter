#include "BTTask_PickUpGun.h"
#include "AIController.h"
#include "../WildWestShooterPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_PickUpGun::UBTTask_PickUpGun() {
    NodeName = TEXT("Pick Up Gun");
}

EBTNodeResult::Type UBTTask_PickUpGun::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) {
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr){
        return EBTNodeResult::Failed;
    }
    
    AWildWestShooterPlayer *ShooterAI = Cast<AWildWestShooterPlayer>(OwnerComp.GetAIOwner()->GetPawn());

    if(ShooterAI== nullptr){
        return EBTNodeResult::Failed;
    }

    ShooterAI->PickUpGun();

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), FVector(0,0,0));
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("CanGetGun"), false);
    OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("HasGun"), true);
    OwnerComp.GetBlackboardComponent()->SetValueAsFloat(TEXT("HandSpeed"), 5.0f);

    return EBTNodeResult::Succeeded;
}