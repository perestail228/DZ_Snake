#include "SnakePawn.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "BonusesInteraction.h"
#include "SnakeElement.h"
#include "MyTimerManager.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "EnhancedInputSubsystems.h"

ASnakePawn::ASnakePawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer),
SnakeMesh(CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Head"))),
FixedCamera(CreateDefaultSubobject<UCameraComponent>(TEXT("FixedCamera")))
{
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = SnakeMesh;
	SnakeMesh->SetRelativeRotation(FRotator{ 0.0f, 0.0f, 0.0f });
	FixedCamera->SetRelativeLocation(FVector{ 0.0f,0.0f,2500.0f });
	FixedCamera->SetRelativeRotation(FRotator{ -90.0f, 0.0f, 0.0f });
	SnakeMesh->OnComponentBeginOverlap.AddDynamic(this, &ASnakePawn::OnComponentBeginOverlap);
}

void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();
	SetActorTickInterval(0.075f);
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ASnakePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (CurrentVelocity != FVector::ZeroVector)
	{
		AddActorWorldOffset(CurrentVelocity * MovementSpeed * DeltaTime, true);
	}
	if (SnakeElements.Num() > 0)
	{
		SnakeElements[0]->SetActorLocation(GetActorLocation());
	}
	for (int32 i = SnakeElements.Num() - 1; i > 0; i--)
	{
		SnakeElements[i]->SetActorLocation(SnakeElements[i - 1]->GetActorLocation());
	}

}

void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) 
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASnakePawn::Move);
	}
}

void ASnakePawn::SpawnChilds()
{
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	FVector SpawnLocation;
	if (SnakeElements.Num() > 0)
	{
		ASnakeElement* LastBodyBlock = SnakeElements[SnakeElements.Num() - 1];
		SpawnLocation = LastBodyBlock->GetActorLocation() - CurrentVelocity * ElementSize;
	}
	else
	{
		SpawnLocation = GetActorLocation() - CurrentVelocity * ElementSize;
	}
	FTransform SnakeElemTransform(FRotator::ZeroRotator, SpawnLocation, FVector::OneVector);
	if (SnakeElementClass != nullptr)
	{
		ASnakeElement* NewBodyBlock = GetWorld()->SpawnActor<ASnakeElement>(SnakeElementClass, SnakeElemTransform, SpawnParams);
		SnakeElements.Add(NewBodyBlock);
		if (SnakeElements.Num() > 6)
		{
			SnakeElements[Counter]->GetMesh()->SetGenerateOverlapEvents(true);
			SnakeElements[Counter]->GetMesh()->OnComponentBeginOverlap.AddDynamic(this, &ASnakePawn::OnComponentBeginForElements);
			Counter++;
		}
	}
}

void ASnakePawn::UpHaste()
{
	MovementSpeed += 10;
}

void ASnakePawn::Move(const FInputActionValue& Value)
{
	FVector InputVector = Value.Get<FVector>();
	if ((InputVector.Y > 0.0f && InputVector.X == 0.0f) && (CurrentVelocity != FVector::BackwardVector))
	CurrentVelocity = FVector::ForwardVector;
	if ((InputVector.Y == 0.0f && InputVector.X > 0.0f) && (CurrentVelocity != FVector::LeftVector))
	CurrentVelocity = FVector::RightVector;
	if ((InputVector.Y == 0.0f && InputVector.X < 0.0f) && (CurrentVelocity != FVector::RightVector))
	CurrentVelocity = FVector::LeftVector;
	if ((InputVector.Y < 0.0f && InputVector.X == 0.0f) && (CurrentVelocity != FVector::ForwardVector))
	CurrentVelocity = FVector::BackwardVector;
}

void ASnakePawn::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	IBonusesInteraction* Bonuses = Cast<IBonusesInteraction>(OtherActor);
	if (Bonuses != nullptr)
	{
		Bonuses->Interact();
		return;
	}
	if (Bonuses == nullptr)
	{
		if (!IsHasTeleport)
		{
			Destroy();
		}
		else
		{
			SetActorLocation(-(OtherActor->GetActorLocation() - (CurrentVelocity * ElementSize)) - FVector(0, 0, 200));
			MyTimerManager<ASnakePawn, void (ASnakePawn::*)()>::DelayFunction(this, "StopTeleportationTimer", 15.0f, &ASnakePawn::StopTeleportationTimer, false);
		}
	}
}

void ASnakePawn::OnComponentBeginForElements(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}

void ASnakePawn::StopTeleportationTimer()
{
	IsHasTeleport = false;
}