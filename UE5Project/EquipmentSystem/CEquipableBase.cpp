#include "Equipment/CEquipableBase.h"
#include "GameFramework/Character.h"
#include "Utilities/CLog.h"

ACEquipableBase::ACEquipableBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	StaticMesh->SetupAttachment(GetRootComponent());
}

void ACEquipableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACEquipableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UPrimitiveComponent* ACEquipableBase::GetMesh()
{
	if (IsValid(StaticMesh))
	{
		return StaticMesh;
	}

	return SkeletalMesh;
}

void ACEquipableBase::AttachActor(FName InSocketName)
{
	if (InSocketName.IsNone())
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("AttachSocketName is None"));
		return;
	}

	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!Character)
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("Character is None"));
		return;
	}

	AttachToComponent(Character->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), InSocketName);
}

void ACEquipableBase::OnEquiped()
{
	bIsEquiped = true;
	AttachActor(AttachSocketName);
}

void ACEquipableBase::OnUnequiped()
{
	if (bIsEquiped)
	{
		bIsEquiped = false;
	}
}

