#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BonusesInteraction.h"
#include "SnakePawn.h"
#include "BonusBase.generated.h"

UCLASS(Abstract)
class SNAKE_API ABonusBase : public AActor,public IBonusesInteraction
{
	GENERATED_BODY()
	
public:	
	ABonusBase() = delete;
	ABonusBase(const FObjectInitializer& objinit);

protected:
	class ASnakePawn* MainPawn;

	virtual void Interact() override { Destroy(); };
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* boxCollision;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Mesh;
};
