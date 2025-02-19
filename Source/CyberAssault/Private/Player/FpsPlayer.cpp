// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FpsPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
AFpsPlayer::AFpsPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraPlayer"));
	CameraComponent->SetupAttachment(RootComponent);

	PlayerMesh = ACharacter::GetMesh();
	PlayerMesh->SetupAttachment(CameraComponent);

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

// End Input System

// Line Trace

void AFpsPlayer::LineTrace()
{
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, CameraComponent->GetComponentLocation(),
		CameraComponent->GetComponentLocation() + CameraComponent->GetForwardVector() * LineTraceDistance,
		ECollisionChannel::ECC_Visibility);

	if (HitResult.bBlockingHit)
	{
		
	}
}

// End Line Trace