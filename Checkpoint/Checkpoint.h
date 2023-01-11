#pragma once
#include "Gameframework/Actor.h"
#include "Components/BoxComponent.h"
#include "Checkpoint.generated.h"

UCLASS()
class ACheckpoint : public AActor
{
	GENERATED_BODY()

	ACheckpoint();

private:

	UPROPERTY(EditAnywhere)
	int ID = 0;

public:

	UFUNCTION()
	void SetIndex(int Index) { ID = Index; }

	UFUNCTION(BlueprintCallable)
	void RemoveCheckpoint();

	UFUNCTION()
	void DestroyCheckpoint();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UBoxComponent* SpawnArea;
};