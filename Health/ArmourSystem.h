#pragma once
#include "ArmourPiece.h"
#include "Components/SceneComponent.h"
#include "ArmourSystem.generated.h"

UCLASS(Blueprintable)
class UArmourSystem : public USceneComponent
{
	GENERATED_BODY()
	UArmourSystem();

private:

	void BeginPlay() override;
	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AArmourPiece* PickedUpPiece;
	AActor* Owner = GetOwner();

	bool bSetPieceLocation = false;
	bool bCheckDistance = false;

	float PieceDistance;

public:

	UFUNCTION(BlueprintCallable)
	void DropArmourPiece(FVector ImpulseForce);
	
	UFUNCTION(BlueprintCallable)
	void PickupArmourPiece(AArmourPiece* PickUp);

	UPROPERTY(EditAnywhere)
	TArray<AArmourPiece*> ArmourPieces;

	// these need to be redone, too confusing with bp
	UPROPERTY(BlueprintReadWrite)
	FVector SpawnLocation = FVector::ZeroVector;
	UFUNCTION(BlueprintCallable)
	void SetNewSpawnLocation(FVector NewSpawnLocation) { SpawnLocation = NewSpawnLocation; }


};