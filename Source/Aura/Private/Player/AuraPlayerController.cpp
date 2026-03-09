// Copyright VQHQ


#include "Player/AuraPlayerController.h"

#include  "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

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

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// Cast the InputComponent to type UEnhancedInputComponent
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	// While MoveAction is being triggered, call the Move function on this PlayerController.
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& InputActionValue)
{
	// W = (0, 1)
	// A = (-1, 0)
	// S = (0, -1)
	// D = (1, 0)
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	// `GetControlRotation()` returns where the **camera/controller is facing**.
	const FRotator Rotation = GetControlRotation();
	// `YawRotation` strips out Pitch and Roll, keeping only the horizontal facing direction.
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X); // "What is forward in THIS local grid, expressed in world space?"
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y); // "What is right in THIS local grid, expressed in world space?"
	
	// Apply the movement to the pawn if it is not null
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}
