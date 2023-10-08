// Base
#include "Character/CCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
// Input
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
// Character State Manage
#include "Components/CCharacterStateComponent.h"
//Interaction
#include "Interfaces/IInteractabl.h"
#include "Kismet/KismetSystemLibrary.h"

// Debug
#include "Utilities/CLog.h"



ACCharacterBase::ACCharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	// Camera Setting
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetCapsuleComponent());
	SpringArm->SetRelativeLocation(FVector(0.0f, 0.0f, 8.5f));
	SpringArm->TargetArmLength = 400.0f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);


	// Pawn Setting
	bUseControllerRotationYaw = false;


	// Character Movement Setting
	//// Default Setting
	GetCharacterMovement()->GravityScale = 1.75f;
	GetCharacterMovement()->MaxAcceleration = 1500.0f;
	GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
	GetCharacterMovement()->bUseSeparateBrakingFriction = true;

	//// Movement/Walk Setting
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.0f;

	//// Movement/Jump & Falling Setting
	GetCharacterMovement()->JumpZVelocity = 700.0f;
	GetCharacterMovement()->AirControl = 0.35f;

	//// Movement/Rotation Setting
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void ACCharacterBase::BeginPlay()
{
	Super::BeginPlay();
}

void ACCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Input Mapping Context Setting
	if (!DefaultMappingContext)
	{
		PrintLine();
		UE_LOG(Caiman, Error, TEXT("DefaultMappingContext is Null"));
		return;
	}

	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Input Action Setting
	EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);

	if (MoveAction)
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACCharacterBase::OnMove);
	}

	if (LookAction)
	{
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACCharacterBase::OnLook);
	}

	if (JumpAction)
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACCharacterBase::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACCharacterBase::StopJumping);
	}

	if (InteractAction)
	{
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACCharacterBase::OnInteract);
	}
}

void ACCharacterBase::OnMove(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void ACCharacterBase::OnLook(const FInputActionValue& Value)
{
	FVector2D MouseVector = Value.Get<FVector2D>();

	AddControllerYawInput(MouseVector.X);
	AddControllerPitchInput(MouseVector.Y);
}

void ACCharacterBase::OnInteract()
{
	// Trace Setting
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation();
	float Radius = 100.0f;

	TArray<TEnumAsByte<EObjectTypeQuery>> HitableObjectTypes;
	TEnumAsByte<EObjectTypeQuery> Interactable = UEngineTypes::ConvertToObjectType(ECollisionChannel::ECC_GameTraceChannel1); // Custom Object Chanel :  Interactable
	HitableObjectTypes.Add(Interactable);

	TArray<AActor*> IgnoreActors;
	IgnoreActors.Add(this);

	TArray<FHitResult> HitResults;

	bool Result = UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		Start,
		End,
		Radius,
		HitableObjectTypes,
		false,
		IgnoreActors,
		EDrawDebugTrace::ForDuration,
		HitResults,
		true
	);

	// Excute
	if (Result)
	{
		for (const FHitResult& HitResult : HitResults)
		{
			IIInteractabl* Interactabl = Cast<IIInteractabl>(HitResult.GetActor());

			if (Interactabl)
			{
				Interactabl->Interact(this);
			}
		}
	}
}