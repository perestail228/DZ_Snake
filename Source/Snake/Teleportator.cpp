#include "Teleportator.h"

ATeleportator::ATeleportator(const FObjectInitializer& objinit): Super(objinit)
{
}

void ATeleportator::Interact()
{
	Super::Interact();
	MainPawn->SetTeleport(true);
}

void ATeleportator::BeginPlay()
{
	Super::BeginPlay();
}
