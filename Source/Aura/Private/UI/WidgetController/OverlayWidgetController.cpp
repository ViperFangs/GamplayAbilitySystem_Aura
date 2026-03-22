// Copyright VQHQ


#include "UI/WidgetController/OverlayWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	// In this case, we do not need the parent function call because the function is empty
	// However, it's good practice to call the parent's function in case it does change
	Super::BroadcastInitialValues();
	
	// Cast the member variable AttributeSet to UAuraAttributeSet to call the functions defined in AuraAttributeSet
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	
	OnHealthChanged.Broadcast(AuraAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AuraAttributeSet->GetMaxHealth());
}
