#include "ArmourSystem.h"

UArmourSystem::UArmourSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UArmourSystem::BeginPlay()
{
	Super::BeginPlay();

	SpawnLocation = Owner->GetActorLocation();
}

void UArmourSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// Distance check before setting collisions back
	//So there's no overlap collision issues
	if(bCheckDistance)
	{
		if (PickedUpPiece == nullptr) return;
	
		PieceDistance = FVector::Dist(Owner->GetActorLocation(), PickedUpPiece->GetActorLocation());
	
		if (PieceDistance >= 300.f)
		{
			PickedUpPiece->ArmourMeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
			PickedUpPiece->ArmourMeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	
			// Check where to point PickedUpPiece
			if (PickedUpPiece == ArmourPieces[0])
			{
				PickedUpPiece = nullptr;
				ArmourPieces.RemoveAt(ArmourPieces.Num() - 1);
				bCheckDistance = false;
			}
			else
			{
				// -1 gets the index -2 gets the previous element in that index
				PickedUpPiece = ArmourPieces[ArmourPieces.Num() - 2];
				ArmourPieces.RemoveAt(ArmourPieces.Num() - 1);
				bCheckDistance = false;
				bSetPieceLocation = true;
			}
		}
	}
}

void UArmourSystem::DropArmourPiece(FVector ImpulseForce)
{
	int LastPieceIndex = ArmourPieces.Num() - 1;

	if (LastPieceIndex < 0)
	{
		// Dead Slime
		// Death goes here
		Owner->SetActorLocation(SpawnLocation);
		GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "DEAD");
		return;
	}
	else
	{
		// Throw armour piece away from the slime and remove it from the array
		bSetPieceLocation = false;

		PickedUpPiece->DropLocation();

		PickedUpPiece->ArmourMeshComponent->SetSimulatePhysics(true);
		PickedUpPiece->ArmourMeshComponent->AddImpulse(ImpulseForce);

		bCheckDistance = true;
	}
}

void UArmourSystem::PickupArmourPiece(AArmourPiece* PickUp)
{
	int PiecesAmount = ArmourPieces.Num();
	// If there are no elements
	// Add the first element
	if ((ArmourPieces.Num() - 1) == (-1)) 
	{
		ArmourPieces.Add(PickUp);

		PickUp->ArmourMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
		PickUp->ArmourMeshComponent->SetSimulatePhysics(false);

		PickUp->SetNewLocation(Owner);

		PickedUpPiece = PickUp;
		bSetPieceLocation = true;
	}
	else 
	{
		for (int i = 0; i < PiecesAmount; i++)
		{
			if (ArmourPieces[i] == PickUp)
			{
				// Quick fix needs to loop through all elements and not add if the first element is wrong
				// Depends on array length ?
				GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, "Loop Return");
				return;
			}
			else
			{
				ArmourPieces.Add(PickUp);

				PickUp->ArmourMeshComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
				PickUp->ArmourMeshComponent->SetSimulatePhysics(false);

				PickUp->SetNewLocation(Owner);

				PickedUpPiece = PickUp;
				bSetPieceLocation = true;
			}
		}
	}
}