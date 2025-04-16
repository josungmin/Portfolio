#include "Items/Weapon/CWeaponBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "RoxyFunctionLibrary.h"

#include "RoxyDebugHelper.h"

ACWeaponBase::ACWeaponBase()
{
    PrimaryActorTick.bCanEverTick = false;
}

void ACWeaponBase::BeginPlay()
{
    Super::BeginPlay();

    AddActorToIgnore(this);
    AddActorToIgnore(GetOwner());
}

void ACWeaponBase::OnEquipWeapon()
{
    if (WeaponState == EWeaponState::Equipped)
    {
        Debug::LogError("Weapon is already equipped.");
        return;
    }

    OnAttach();
    WeaponState = EWeaponState::Equipped;
}

void ACWeaponBase::OnUnequipWeapon()
{
    if (WeaponState != EWeaponState::Equipped)
    {
        Debug::LogError("Weapon is not equipped.");
        return;
    }

    OnDetach();
    WeaponState = EWeaponState::Unequipped;
}

void ACWeaponBase::StartTrace()
{
    if (WeaponState != EWeaponState::Equipped)
    {
        Debug::LogWarning("Weapon must be equipped before starting trace.");
        return;
    }
    
    bIsTracing = true;
    WeaponState = EWeaponState::Tracing;
    AlreadyHitActors.Empty();
}

void ACWeaponBase::StopTrace()
{
    if (WeaponState != EWeaponState::Tracing)
    {
        return;
    }

    bIsTracing = false;
    WeaponState = EWeaponState::Equipped;
    AlreadyHitActors.Empty();
}

void ACWeaponBase::PerformSweep()
{
    if (!IsValid(GetMesh()))
    {
        Debug::LogError("Weapon Mesh is not vaild");
        return;
    }

    if (!bIsTracing)
    {
        return;
    }

    FVector Start = GetMesh()->GetSocketLocation(TraceStartSocketName);
    FVector End = GetMesh()->GetSocketLocation(TraceEndSocketName);

    FCollisionQueryParams CollisionParams;
    for (AActor* Actor : ActorsToIgnore)
    {
        CollisionParams.AddIgnoredActor(Actor);
    }

    FCollisionObjectQueryParams CollisionObjectPrams(CollisionObjectTypes);

    TArray<FHitResult> HitResults;
    const bool bHit = GetWorld()->SweepMultiByObjectType(
        HitResults,
        Start,
        End,
        FQuat::Identity,
        CollisionObjectPrams,
        FCollisionShape::MakeSphere(TraceRadius),
        CollisionParams
    );

    if (bHit)
    {
        for (const FHitResult& HitResult : HitResults)
        {
            AActor* HitActor = HitResult.GetActor();
            if (!HitActor || AlreadyHitActors.Contains(HitActor))
            {
                continue;
            }

            AlreadyHitActors.Add(HitActor);

            APawn* OwnerPawn = Cast<APawn>(GetOwner());
            APawn* HitPawn = Cast<APawn>(HitActor);

            if (OwnerPawn && HitPawn)
            {
                if (URoxyFunctionLibrary::IsHostileToTarget(OwnerPawn, HitPawn))
                {
                    FWeaponHitInfo HitInfo;
                    HitInfo.HitActor = HitResult.GetActor();
                    HitInfo.HitLocation = HitResult.ImpactPoint;

                    OnWeaponHitTarget.ExecuteIfBound(HitInfo);
                }
            }
        }
    }

    // TODO: Debug
    DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 1.0f, 0, 1.0f);
    DrawDebugSphere(GetWorld(), Start, TraceRadius, 12, FColor::Green, false, 1.0f);
}
