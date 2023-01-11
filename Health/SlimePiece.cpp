#include "SlimePiece.h"

ASlimePiece::ASlimePiece()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SlimePiece"));
	SphereComp->SetupAttachment(RootComponent);
}

void ASlimePiece::ApplyImpulse(FVector Velocity)
{
	SphereComp->AddImpulse(Velocity);
}
