#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SnakeElement.generated.h"

UCLASS()
class SNAKE_API ASnakeElement : public AActor
{
	GENERATED_BODY()
	
public:	
	ASnakeElement() = delete;
	ASnakeElement(const FObjectInitializer& ObjectInitializer);
	UStaticMeshComponent* GetMesh() { return SnakeElementMesh; };
private:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* SnakeElementMesh;
};
