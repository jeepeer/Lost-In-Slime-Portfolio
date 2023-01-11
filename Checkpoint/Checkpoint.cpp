#include "Checkpoint.h"
#include "Components/BoxComponent.h"
#include "CheckpointSystem.h"

ACheckpoint::ACheckpoint()
{
	SpawnArea = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnArea"));
	RootComponent = SpawnArea;
}

void ACheckpoint::RemoveCheckpoint()
{
	Cast<ACheckpointSystem>(GetAttachParentActor())->UpdateCheckpoints(ID);
}

void ACheckpoint::DestroyCheckpoint()
{
	Destroy();
}
