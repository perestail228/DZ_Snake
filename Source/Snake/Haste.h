#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "Haste.generated.h"

UCLASS()
class SNAKE_API AHaste : public ABonusBase
{
	GENERATED_BODY()

public:
	AHaste() = delete;
	AHaste(const FObjectInitializer& objinit);

private:
	virtual void Interact() override;
	virtual void BeginPlay() override;
};
