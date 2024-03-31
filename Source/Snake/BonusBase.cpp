#include "BonusBase.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

ABonusBase::ABonusBase(const FObjectInitializer& objinit): Super(objinit),
boxCollision(CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"))),
Mesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh")))
{
	RootComponent = Mesh;
	boxCollision->SetupAttachment(Mesh);
	PrimaryActorTick.bCanEverTick = false;
}

void ABonusBase::BeginPlay()
{
	Super::BeginPlay();
	MainPawn = Cast<ASnakePawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
}

