#include "SlimeHealthSystem.h"
#include "GP4Team3/Character/SlimePawn.h"

USlimeHealthSystem::USlimeHealthSystem()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USlimeHealthSystem::BeginPlay()
{
	Super::BeginPlay();
	
}

void USlimeHealthSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if(bCheckForDistance)
	{
		CheckForDistance();
	}
}

void USlimeHealthSystem::CheckForDistance()
{
	if (Piece == nullptr) return;

	DistanceFromPiece = FVector::Dist(Piece->GetActorLocation(), Owner->GetActorLocation());
	if (DistanceFromPiece >= 300.f) 
	{
		// if the piece is more or equal to 3m away from the slime
		// set it's collisions so it can interact with ground
		Piece->SphereComp->SetCollisionResponseToAllChannels(ECR_Overlap);
		Piece->SphereComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
		// set pointer to nullptr so there's no funny interactions
		Piece = nullptr;
		// stop the tick event
		bCheckForDistance = false;
	}
}

void USlimeHealthSystem::AddHealth()
{
	// Gets called from BP_SlimePiece
	if (CurrentHealth == 2) { return; }
	else
	{
		CurrentHealth++;
		OnHealthChange.Broadcast(CurrentHealth);
	}
}

void USlimeHealthSystem::RemoveHealth(FVector Velocity)
{
	if (CurrentHealth <= 0) 
	{
		// Death
		SlimeDeath();
		return;
	}
	else 
	{
		// Drop slime piece and decrease current health
		// Slime gets spawned in Blueprints
		
		// Applies impulse to make the piece fly out of the SlimePawn
		Piece->ApplyImpulse(Velocity);

		CurrentHealth--;
		OnHealthChange.Broadcast(CurrentHealth);
		// starts CheckForDistance() in TickComponent()
		bCheckForDistance = true;
	}
}

void USlimeHealthSystem::SetPiecePointer(ASlimePiece* SlimePiece)
{
	// Called from BP_SlimeHealthSystem
	Piece = SlimePiece;
}

void USlimeHealthSystem::SetCheckpointLocation(FVector Location)
{
	// This is called from BP_Checkpoint
	CheckpointLocation = Location;
}

void USlimeHealthSystem::SlimeDeath()
{
	// Called from BP_DeathBox
	Owner->SetActorLocation(CheckpointLocation);
	CurrentHealth = 2;
	OnHealthChange.Broadcast(CurrentHealth);
}
