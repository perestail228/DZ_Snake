#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "Teleportator.generated.h"

UCLASS()
class SNAKE_API ATeleportator : public ABonusBase
{
	GENERATED_BODY()

public:
	ATeleportator() = delete;
	ATeleportator(const FObjectInitializer& objinit);

private:
	virtual void Interact() override;
	virtual void BeginPlay() override;
};
