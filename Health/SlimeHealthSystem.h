#pragma once
#include "Components/SceneComponent.h"
#include "SlimePiece.h"
#include "GP4Team3/Checkpoints/CheckpointSystem.h"
#include "SlimeHealthSystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthChange, int, newHealth);

UCLASS(Blueprintable)
class USlimeHealthSystem : public USceneComponent
{
	GENERATED_BODY()
	USlimeHealthSystem();

private:

	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	FVector CheckpointLocation = FVector::ZeroVector;

	void CheckForDistance();
	float DistanceFromPiece = 0.f;

	bool bCheckForDistance = false;

	AActor* Owner = GetOwner();
	ASlimePiece* Piece;
	ACheckpointSystem* Checkpoint;

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentHealth = 2;

	UFUNCTION(BlueprintCallable)
	void AddHealth();

	UFUNCTION(BlueprintCallable)
	void RemoveHealth(FVector Velocity);

	UFUNCTION(BlueprintCallable)
	void SetPiecePointer(ASlimePiece* SlimePiece);

	UFUNCTION(BlueprintCallable)
	void SetCheckpointLocation(FVector Location);

	UFUNCTION(BlueprintCallable)
	void SlimeDeath();

	FOnHealthChange OnHealthChange;
};