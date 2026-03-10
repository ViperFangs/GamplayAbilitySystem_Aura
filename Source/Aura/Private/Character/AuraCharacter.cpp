// Copyright VQHQ


#include "Character/AuraCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

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
