#include "SnakeElement.h"

ASnakeElement::ASnakeElement(const FObjectInitializer& ObjectInitializer):Super(ObjectInitializer),
SnakeElementMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh")))
{
	RootComponent = SnakeElementMesh;
	PrimaryActorTick.bCanEverTick = false;
}

