#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BrainComponent.h"


void AEnemyAIController::BeginPlay() {
    Super::BeginPlay();

    EnableAI();

    APawn* AIPawn = GetPawn();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(AIBehavior){
        if(AIPawn && PlayerPawn){
            GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
        }
    }
}

void AEnemyAIController::EnableAI(){
    RunBehaviorTree(AIBehavior);
}

void AEnemyAIController::DisableAI(){
    GetBrainComponent()->StopLogic(TEXT("Disabled during countdown"));;
}