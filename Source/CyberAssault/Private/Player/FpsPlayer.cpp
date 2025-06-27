// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FpsPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interface/FpsInterface.h"

// Sets default values
AFpsPlayer::AFpsPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraPlayer"));
	CameraComponent->SetupAttachment(RootComponent);
	CameraComponent->bUsePawnControlRotation = true;
	
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(CameraComponent);

	PlayerMesh = ACharacter::GetMesh();
	PlayerMesh->SetupAttachment(SpringArm);

}

// Called when the game starts or when spawned
void AFpsPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFpsPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	LineTrace();
}

// Called to bind functionality to input
void AFpsPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(InputMappingContext, 0);
			
			if (UEnhancedInputComponent* FPSEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
			{
				FPSEnhancedInput->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFpsPlayer::MoveEnhancedInput);
				FPSEnhancedInput->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFpsPlayer::LookEnhancedInput);
				FPSEnhancedInput->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
				FPSEnhancedInput->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
				FPSEnhancedInput->BindAction(InteractAction, ETriggerEvent::Started, this, &AFpsPlayer::InteractEnhancedInput);
			}
		}
	}
	
}

// New Input System

void AFpsPlayer::MoveEnhancedInput(const FInputActionValue& Value)
{
	FVector2d MovementVector = Value.Get<FVector2d>();
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AFpsPlayer::LookEnhancedInput(const FInputActionValue& Value)
{
	FVector2d LookValue = Value.Get<FVector2d>();
	AddControllerYawInput(LookValue.X * MouseSensitivityYaw);
	AddControllerPitchInput(LookValue.Y * MouseSensitivityPitch);
}

void AFpsPlayer::InteractEnhancedInput(const FInputActionValue& Value)
{
	if (LineTraceHitResult.bBlockingHit)
	{
		if (AActor* HitActor = LineTraceHitResult.GetActor())
		{
			if (IFpsInterface* ImplementedActor = Cast<IFpsInterface>(HitActor))
			{
				ImplementedActor->Execute_PlayerInteract(HitActor);
			}
		}
	}
}

// End Input System

// Line Trace

void AFpsPlayer::LineTrace()
{
	if (AActor* HitActor = LineTraceHitResult.GetActor())
	{
		if (IFpsInterface* ActorInterface = Cast<IFpsInterface>(HitActor))
		{
			CachedHitActor = HitActor;
		}
		else
		{
			PlayerHideShowMessage();
		}
	}

	
	GetWorld()->LineTraceSingleByChannel(LineTraceHitResult, CameraComponent->GetComponentLocation(),
		CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * LineTraceDistance,
		ECollisionChannel::ECC_Visibility);
	
	if (LineTraceHitResult.bBlockingHit)
	{
		PlayerShowMessage();
	}
	else
	{
		PlayerHideShowMessage();
	}
}

void AFpsPlayer::PlayerShowMessage()
{
	if (AActor* HitActor = LineTraceHitResult.GetActor())
	{
		if (IFpsInterface* ActorInterface = Cast<IFpsInterface>(HitActor))
		{
			ActorInterface->Execute_ShowMessage(HitActor);
		}
	}
}

void AFpsPlayer::PlayerHideShowMessage()
{
	if (IFpsInterface* ActorInterface = Cast<IFpsInterface>(CachedHitActor))
	{
		ActorInterface->Execute_HideMessage(CachedHitActor);
	}
}

// End Line Trace

// Grabbed

void AFpsPlayer::SpawnWeapon()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Weapon Spawned VAR CPP!"));
	}
}

// End Grabbed