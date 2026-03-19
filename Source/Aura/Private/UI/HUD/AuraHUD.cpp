// Copyright VQHQ


#include "UI/HUD/AuraHUD.h"

#include "UI/Widget/AuraUserWidget.h"

void AAuraHUD::BeginPlay()
{
	Super::BeginPlay();
	
	// Create a local widget variable based on the OverlayWidgetClass which can set by another class such as the WidgetController
	UUserWidget* Widget = CreateWidget<UUserWidget>(GetWorld(), OverlayWidgetClass);
	// Set the Widget to the viewport
	Widget->AddToViewport();
}
