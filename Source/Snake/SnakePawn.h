#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "SnakePawn.generated.h"

class ASnakeElement;

UCLASS()
class SNAKE_API ASnakePawn : public APawn
{
	GENERATED_BODY()

public:
	ASnakePawn() = delete;
	ASnakePawn(const FObjectInitializer& ObjectInitializer);
	void SpawnChilds();
	void UpHaste();
	void SetTeleport(bool HasTeleport) { this->IsHasTeleport = HasTeleport; };

private:
	UPROPERTY(EditAnywhere,meta = (AllowPrivateAccess = "true"))
	float MovementSpeed;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	float ElementSize;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ASnakeElement> SnakeElementClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SnakeMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FixedCamera;
	UPROPERTY()
	TArray<class ASnakeElement*> SnakeElements;

	FTimerHandle TeleportTimerHandle;
	FVector CurrentVelocity;
	int Counter = 6;
	float TickInterval = 1.0f;
	bool IsHasTeleport = false;


	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnComponentBeginForElements(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void StopTeleportationTimer();
	void Move(const struct FInputActionValue& Value);
};