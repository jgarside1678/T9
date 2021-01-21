// Copyright T9 2020


#include "AI_IsResInventoryFull_Decorator.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"

#include "AI_Controller.h"
#include "T9/Characters/Alliance/Alliance_ResourceGatherer.h"

UAI_IsResInventoryFull_Decorator::UAI_IsResInventoryFull_Decorator(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	NodeName = "Is Resource Inventory Full";
	bNotifyBecomeRelevant = true;
	bNotifyCeaseRelevant = true;
}




bool UAI_IsResInventoryFull_Decorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAI_Controller* Controller = Cast<AAI_Controller>(OwnerComp.GetAIOwner());
	AAlliance_ResourceGatherer* NPC = Cast<AAlliance_ResourceGatherer>(Controller->GetPawn());
	bool Full = NPC->CheckFullInventory();
	return !Full;
}

