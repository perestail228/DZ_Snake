#include "Haste.h"

AHaste::AHaste(const FObjectInitializer& objinit) : Super(objinit)
{
}

void AHaste::Interact()
{
	Super::Interact();
	MainPawn->UpHaste();
}

void AHaste::BeginPlay()
{
	Super::BeginPlay();
}


