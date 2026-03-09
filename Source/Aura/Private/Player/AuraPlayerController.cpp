// Copyright VQHQ


#include "Player/AuraPlayerController.h"

#include  "EnhancedInputSubsystems.h"

AAuraPlayerController::AAuraPlayerController()
{
	// Allows a change to be replicated to all clients.
	bReplicates = true;
}

void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();
	// If input is not working, error out.
	// Assert that the AuraContext pointer is resolved.
	check(AuraContext);
	
	// Get the Enhanced Input subsystem that belongs to "this" player.
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	// Assert that the Subsystem pointer is resolved.
	check(Subsystem);

	// Add the AuraContext to "this player".
	// AuraContext contains the default input for the player.
	Subsystem->AddMappingContext(AuraContext, 0);
	
	// Show the mouse cursor
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;
	
	// Create an Input Mode to receive player input from both the game and the UI.
	FInputModeGameAndUI InputModeData;
	// Do not lock the mouse to the viewport.
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// Do not hide the cursor when it is in the viewport.
	InputModeData.SetHideCursorDuringCapture(false);
	// Apply the mouse settings to the player controller
	SetInputMode(InputModeData);
}
