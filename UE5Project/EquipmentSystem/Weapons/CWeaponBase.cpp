#include "Equipment/Weapons/CWeaponBase.h"
#include "Character/CCombatCharacterBase.h"
#include "Interfaces/IWeapon.h"
#include "Components/CCombatComponent.h"
#include "Components/CCollisionComponent.h"
#include "Kismet/GameplayStatics.h"

// Dubug
#include "Utilities/CLog.h"

ACWeaponBase::ACWeaponBase()
{
	SkeletalMesh->SetNotifyRigidBodyCollision(true); // Simulation Generates Hit Events
	SkeletalMesh->SetGenerateOverlapEvents(true);
	SkeletalMesh->SetCollisionProfileName(FName("OverlapAll")); // Collision Preset

	StaticMesh->SetNotifyRigidBodyCollision(true);
	StaticMesh->SetGenerateOverlapEvents(true);
	StaticMesh->SetCollisionProfileName(FName("OverlapAll"));


	// CollisionComponent Setting
	CollisionComponent = CreateDefaultSubobject<UCCollisionComponent>(TEXT("CollisionComponent"));

	CollisionComponent->OnHit.BindUFunction(this, FName("OnHit"));
	CollisionComponent->AddIgnoreActor(GetOwner());
}

ACWeaponBase* ACWeaponBase::Spawn(UWorld* InWorld, UClass* InClass, AActor* InOwner = NULL)
{
	if (!InWorld)
	{
		return NULL;
	}

	if (!InClass)
	{
		return NULL;
	}

	FActorSpawnParameters params;
	params.Owner = InOwner;

	AActor* SpawnedActor = InWorld->SpawnActor(InClass, NULL, NULL, params);

	return SpawnedActor != NULL ? Cast<ACWeaponBase>(SpawnedActor) : NULL;
}

void ACWeaponBase::OnEquiped()
{
	Super::OnEquiped();

	ACCombatCharacterBase* OwnerCharacter = Cast<ACCombatCharacterBase>(GetOwner());
	if (!OwnerCharacter)
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("OwnerCharacter is Null"));
		return;
	}

	UCCombatComponent* CombatComponent = OwnerCharacter->FindComponentByClass<UCCombatComponent>();
	if (!CombatComponent)
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("CombatComponent is Null"));
		return;
	}

	CombatComponent->SetMainWeapon(this);

	// Update Animation 
	IIWeapon* AnimBP = Cast<IIWeapon>(OwnerCharacter->GetMesh()->GetAnimInstance());
	AnimBP->SetWeaponType(WeaponType);

	// Collision Setting
	CollisionComponent->SetCollisionMesh(GetMesh());
}

void ACWeaponBase::OnHit(FHitResult InHitResult)
{
	UGameplayStatics::ApplyPointDamage(
		InHitResult.GetActor(),
		Damage,
		GetOwner()->GetActorForwardVector(),
		InHitResult,
		GetInstigatorController(),
		this,
		NULL
	);
}
