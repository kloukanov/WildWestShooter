#include "BTTask_Shoot.h"
#include "AIController.h"
#include "../WildWestShooterPlayer.h"

UBTTask_Shoot::UBTTask_Shoot() {
    NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) {
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr){
        return EBTNodeResult::Failed;
    }
    
    AWildWestShooterPlayer *ShooterAI = Cast<AWildWestShooterPlayer>(OwnerComp.GetAIOwner()->GetPawn());

    if(ShooterAI== nullptr){
        return EBTNodeResult::Failed;
    }

    ShooterAI->Shoot();

    return EBTNodeResult::Succeeded;
}