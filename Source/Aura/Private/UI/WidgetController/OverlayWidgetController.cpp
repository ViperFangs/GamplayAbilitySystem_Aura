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

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	// In this case, we do not need the parent function call because the function is empty
	// However, it's good practice to call the parent's function in case it does change
	Super::BindCallbacksToDependencies();
	
	// Cast the member variable AttributeSet to UAuraAttributeSet to call the functions defined in AuraAttributeSet
	const UAuraAttributeSet* AuraAttributeSet = Cast<UAuraAttributeSet>(AttributeSet);
	
	// Whenever the Attribute changes, the AttributeChanged function will be called (Add a callback function)
	// In this case, when health changes, the HealthChanged function will be called
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AuraAttributeSet->GetMaxHealthAttribute()).AddUObject(this, &UOverlayWidgetController::MaxHealthChanged);
}

// This function needs to take FOnAttributeChangeData as a parameter to work with the GetGameplayAttributeValueChangeDelegate
// FOnAttributeChangeData Object will contain the details of the change
void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	// Broadcast the new value of Health
	OnHealthChanged.Broadcast(Data.NewValue);
}

// This function needs to take FOnAttributeChangeData as a parameter to work with the GetGameplayAttributeValueChangeDelegate
void UOverlayWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	// Broadcast the new value of MaxHealth
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}
