// Copyright VQHQ


#include "CHaracter/AuraCharacterBase.h"

AAuraCharacterBase::AAuraCharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Initialize a Subobject for a Weapon
	Weapon = CreateDefaultSubobject<USkeletalMeshComponent>("Weapon");
	// Attach the weapon to a socket on the Skeleton Mesh
	// GetMesh is a function inherited from the ACharacter class 
	Weapon->SetupAttachment(GetMesh(), FName("WeaponHandSocket"));
	// Disable weapon collision
	Weapon->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AAuraCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

