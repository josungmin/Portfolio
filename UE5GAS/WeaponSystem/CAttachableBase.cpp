#include "Items/CAttachableBase.h"
#include "GameFramework/Character.h"

#include "RoxyDebugHelper.h"

ACAttachableBase::ACAttachableBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("SceneComponent"));
	SetRootComponent(SceneComponent);

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	SkeletalMesh->SetupAttachment(GetRootComponent());

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(GetRootComponent());
}

UPrimitiveComponent* ACAttachableBase::GetMesh()
{
	if (StaticMesh && StaticMesh->GetStaticMesh())
	{
		return StaticMesh;
	}

	if (SkeletalMesh)
	{
		return SkeletalMesh;
	}

	Debug::LogError(TEXT("Both StaticMesh and SkeletalMesh are invalid"));

	return nullptr;
}

void ACAttachableBase::OnAttach(FName InSocketName)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if (!IsValid(Character))
	{
		Debug::LogError("Character is not valid");
		return;
	}

	USkeletalMeshComponent* CharacterMesh = Character->GetMesh();
	if (!CharacterMesh)
	{
		Debug::LogError(TEXT("Character Mesh is not valid"));
		return;
	}

	FName SocketToUse = InSocketName.IsNone() ? AttachSocketName : InSocketName;

	if (!AttachToComponent(CharacterMesh, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), SocketToUse))
	{
		Debug::LogError(FString::Printf(TEXT("AttachToComponent failed for socket: %s"), *SocketToUse.ToString()));
		return;
	}
}

void ACAttachableBase::OnDetach()
{
	DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
}
