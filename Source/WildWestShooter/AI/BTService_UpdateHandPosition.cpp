#include "BTService_UpdateHandPosition.h"
#include "AIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../WildWestShooterPlayer.h"

UBTService_UpdateHandPosition::UBTService_UpdateHandPosition() {
    NodeName = TEXT("Update Hand Position");
    bNotifyBecomeRelevant = true;
}

void UBTService_UpdateHandPosition::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) {
    Super::OnBecomeRelevant(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr){
        return;
    }

    ShooterAI = Cast<AWildWestShooterPlayer>(OwnerComp.GetAIOwner()->GetPawn());
}

void UBTService_UpdateHandPosition::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) {
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    // straight down = FVector2D(0,-30)
    // straight forward = FVector2D(0,0)

    if(ShooterAI) {
        bool HasGun = OwnerComp.GetBlackboardComponent()->GetValueAsBool("HasGun");
        if(ShooterAI->CanGetGun() && HasGun == false){
            OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
        }

        FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector("TargetLocation");
        float HandSpeed = OwnerComp.GetBlackboardComponent()->GetValueAsFloat("HandSpeed");
        FVector2D NewLocation = FMath::Vector2DInterpTo(ShooterAI->GetLookAxisVector(), FVector2D(TargetLocation.X, TargetLocation.Y), DeltaSeconds, HandSpeed);
        ShooterAI->SetLookAxisVector(NewLocation);
    }
}
