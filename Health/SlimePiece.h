#pragma once
#include "Gameframework/Actor.h"
#include "Components/SphereComponent.h"
#include "SlimePiece.generated.h"

UCLASS()
class ASlimePiece : public AActor 
{
	GENERATED_BODY()
	ASlimePiece();

private:

public:

	UFUNCTION()
	void ApplyImpulse(FVector Velocity);

	UPROPERTY(EditDefaultsOnly)
	USphereComponent* SphereComp;
};