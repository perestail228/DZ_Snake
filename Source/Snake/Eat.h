#pragma once

#include "CoreMinimal.h"
#include "BonusBase.h"
#include "Eat.generated.h"

UCLASS()
class SNAKE_API AEat : public ABonusBase
{
	GENERATED_BODY()

public:
	AEat() = delete;
	AEat(const FObjectInitializer& objinit);

private:
	virtual void Interact() override;
	virtual void BeginPlay() override;
};
