#include "Components/CCollisionComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Utilities/CLog.h"

UCCollisionComponent::UCCollisionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCCollisionComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UCCollisionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (bIsCollisionEnabled)
	{
		CollisionTrace();
	}
}

void UCCollisionComponent::AddIgnoreActor(AActor* InActor)
{
	if (!IgnoreActors.Contains(InActor))
	{
		IgnoreActors.Add(InActor);
	}
}

void UCCollisionComponent::SetCollisionMesh(UPrimitiveComponent* MeshComp)
{
	CollisionMeshComponent = MeshComp;
}

void UCCollisionComponent::EnableCollision()
{
	ClreatHitActors();
	bIsCollisionEnabled = true;
}

void UCCollisionComponent::DisableCollision()
{
	bIsCollisionEnabled = false;
}

void UCCollisionComponent::CollisionTrace()
{
	// Initialization
	const FVector Start = CollisionMeshComponent->GetSocketLocation(StartSocketName);
	const FVector End = CollisionMeshComponent->GetSocketLocation(EndSocketName);

	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActors(IgnoreActors);

	TArray<FHitResult> HitResults;
	FCollisionObjectQueryParams CollisionObjectPrams(CollisionObjectType);
	
	const bool Result = GetWorld()->SweepMultiByObjectType(HitResults, Start, End, FQuat::Identity, CollisionObjectPrams, FCollisionShape::MakeSphere(TraceRadius), CollisionParams);

	bool DrawDebug = false; // TODO: 디버그용 임시코드

	// Excute
	if (Result)
	{
		for (const FHitResult& HitResult : HitResults)
		{
			bool IsDuplicate = AlreadyHitActors.Contains(HitResult.GetActor());
			if (IsDuplicate) continue;

			UE_LOG(Caiman, Error, TEXT("%s"), *HitResult.GetActor()->GetName());

			AlreadyHitActors.Add(HitResult.GetActor());
			if (OnHit.IsBound())
			{
				DrawDebug = true; // TODO: 디버그용 임시코드
				OnHit.Execute(HitResult);
			}
		}
	}


#if ENABLE_DRAW_DEBUG
	FVector CapsulePosition = Start + (End - Start) / 2.0f;
	float HalfHeight = (End - Start).Size() / 2.0f;
	FColor color = DrawDebug ? FColor::Green : FColor::Red;
	FRotator TraceRotation = UKismetMathLibrary::FindLookAtRotation(Start, End);

	DrawDebugCapsule(GetWorld(), CapsulePosition, HalfHeight, TraceRadius, FRotationMatrix::MakeFromZ(TraceRotation.Vector()).ToQuat(), color, false, 3.0f);
#endif

	DrawDebug = false; // TODO: 디버그용 임시코드
}

void UCCollisionComponent::ClreatHitActors()
{
	AlreadyHitActors.Empty();
}

