// Copyright VQHQ


#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/AuraPlayerState.h"

AAuraCharacter::AAuraCharacter()
{
	// Character should face in the direction it moves
	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Rotates the Yaw at a set speed 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f);
	// Lock movement to a flat plane
	GetCharacterMovement()->bConstrainToPlane = true;
	// Snap to the plane immediately on start
	GetCharacterMovement()->bSnapToPlaneAtStart = true;
	
	// Let bOrientRotationToMovement handle rotation instead of the controller handling the rotation
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState)
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this);
	
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	AttributeSet = AuraPlayerState->GetAttributeSet();
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	// Init ability actor info for the Server
	InitAbilityActorInfo();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	// Init ability actor info for the Client
	InitAbilityActorInfo();
}
