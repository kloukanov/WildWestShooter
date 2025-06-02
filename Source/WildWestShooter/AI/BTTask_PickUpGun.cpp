#include "BTTask_PickUpGun.h"
#include "AIController.h"
#include "../WildWestShooterPlayer.h"

UBTTask_PickUpGun::UBTTask_PickUpGun() {
    NodeName = TEXT("Shoot");
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

    return EBTNodeResult::Succeeded;
}