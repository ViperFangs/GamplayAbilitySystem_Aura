// Copyright VQHQ

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "OverlayWidgetController.generated.h"

// Delegate type that broadcasts a float (example: NewHealth) to all listeners when Health changes.
// Any function binding to this must accept a float parameter.
// The signature is just the shape of the function it expects, it doesn't exist yet. We are defining the TYPE here.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float, NewHealth);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMaxHealthChangedSignature, float, NewMaxHealth);

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class AURA_API UOverlayWidgetController : public UAuraWidgetController
{
	GENERATED_BODY()

public:
	// This function will be used to initialize the default values on the overlay
	virtual void BroadcastInitialValues() override;
	
	// Create member variables for the class
	// These are the INSTANCES of the TYPE defined in the delegate function created.
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnHealthChangedSignature OnHealthChanged;
	
	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnMaxHealthChangedSignature OnMaxHealthChanged;
};
