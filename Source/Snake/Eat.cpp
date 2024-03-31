#include "Eat.h"

AEat::AEat(const FObjectInitializer& objinit) : Super(objinit)
{
}

void AEat::Interact()
{
	Super::Interact();
	MainPawn->SpawnChilds();
}

void AEat::BeginPlay()
{
	Super::BeginPlay();
}
