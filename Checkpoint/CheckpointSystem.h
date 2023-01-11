#pragma once
#include "Gameframework/Actor.h"
#include "Checkpoint.h"
#include "CheckpointSystem.generated.h"

UCLASS()
class ACheckpointSystem : public AActor
{
	GENERATED_BODY()

private:

	void BeginPlay() override;

	void UpdateArrayIndices();

	int NewIndex = 0;
	int NumberOfElements = 0;

	FVector CurrentCheckpoint = FVector::ZeroVector;

	ACheckpoint* RemovedElement;

public:

	UFUNCTION(BlueprintCallable)
	void UpdateCheckpoints(int index);

	UFUNCTION(BLueprintCallable)
	FVector GetCheckpointLocation();

	UPROPERTY(EditAnywhere)
	TArray<AActor*> Checkpoints;
};