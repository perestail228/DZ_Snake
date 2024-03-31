#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "BonusesInteraction.generated.h"

UINTERFACE(MinimalAPI)
class UBonusesInteraction : public UInterface
{
	GENERATED_BODY()
};


class SNAKE_API IBonusesInteraction
{
	GENERATED_BODY()

public:
	virtual void Interact() = 0;
};
