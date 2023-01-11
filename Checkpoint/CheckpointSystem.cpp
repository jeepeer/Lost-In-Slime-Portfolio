#include "CheckpointSystem.h"

void ACheckpointSystem::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> TempArray;
	GetAttachedActors(TempArray);

	for (int i = TempArray.Num() - 1; i >= 0; i--)
	{
		Checkpoints.Add(TempArray[i]);
		Cast<ACheckpoint>(Checkpoints[NewIndex])->SetIndex(NewIndex);
		NewIndex++;
	}

	TempArray.Empty();
}

void ACheckpointSystem::UpdateArrayIndices()
{
	NewIndex = 0;
	for (int i = 0; i < Checkpoints.Num(); i++)
	{
		Cast<ACheckpoint>(Checkpoints[i])->SetIndex(NewIndex);
		NewIndex++;
	}
}

void ACheckpointSystem::UpdateCheckpoints(int index)
{
	CurrentCheckpoint = Checkpoints[index]->GetActorLocation();

	for (int i = 0; i < Checkpoints.Num(); i++)
	{
		NumberOfElements++;
		Cast<ACheckpoint>(Checkpoints[i])->DestroyCheckpoint();

		if (i == index)
		{			
			if (index == 0)
			{
				Checkpoints.RemoveAt(0, 1);
				UpdateArrayIndices();

				NumberOfElements = 0;
				return;
			}
			else
			{
				Checkpoints.RemoveAt(0, NumberOfElements);
				UpdateArrayIndices();

				NumberOfElements = 0;
				return;
			}
		}
	}
}

FVector ACheckpointSystem::GetCheckpointLocation()
{
	return CurrentCheckpoint + (FVector::UpVector * 300.f);
}
