// Copyright VQHQ


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

UOverlayWidgetController* AAuraHUD::GetOverlayWidgetController(const FWidgetControllerParams& WCParams)
{
	// Construct the OverlayWidgetController if it hasn't been constructed yet
	if (OverlayWidgetController == nullptr)
	{
		// Create a new OverlayWidgetController of class OverlayWidgetControllerClass
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
		OverlayWidgetController->SetWidgetControllerParams(WCParams);
		// We are binding the callback functions when setting up the OverlayWidgetController
		// This will ensure any changes made to the Attributes will be broadcasted to whoever is listening
		OverlayWidgetController->BindCallbacksToDependencies();
		return OverlayWidgetController;
	}
	
	return OverlayWidgetController;
}

void AAuraHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(OverlayWidgetClass, TEXT("Overlay Widget Class uninitialized, please fill out BP_AuraHUD"));
	checkf(OverlayWidgetControllerClass, TEXT("Overlay Widget Controller Class uninitialized, please fill out BP_AuraHUD"));
	
	// Create a local widget variable based on the OverlayWidgetClass which can set by another class such as the WidgetController
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	OverlayWidget = Cast<UAuraUserWidget>(Widget);
	
	// Create a widget controller using the function parameters
	const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
	// Initialize a WidgetController if not created yet
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetControllerParams);
	
	// Set the WidgetController we created to the OverlayWidget controller.
	OverlayWidget->SetWidgetController(WidgetController);
	
	// Broadcast the initial values for the Overlay, we need to make sure this is called after SetWidgetController as all the variables needed by the controller will be initialized.
	WidgetController->BroadcastInitialValues();
	
	// Set the Widget to the viewport
	Widget->AddToViewport();
}