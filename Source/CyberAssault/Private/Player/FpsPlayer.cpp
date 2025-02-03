// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/FpsPlayer.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputSubsystems.h"

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

}

// Called to bind functionality to input
void AFpsPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	//Super::SetupPlayerInputComponent(PlayerInputComponent);

	//InputComponent->BindAxis("MoveForward", this, &AFpsPlayer::MoveForward);
	//InputComponent->BindAxis("MoveRight", this, &AFpsPlayer::MoveRight);
	//InputComponent->BindAxis("LookUp", this, &AFpsPlayer::LookUp);
	//InputComponent->BindAxis("TurnRight", this, &AFpsPlayer::TurnRight);

	//InputComponent->BindAction("Jump", IE_Pressed, this, &AFpsPlayer::PlayerJump);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			SubSystem->AddMappingContext(InputMappingContext, 0);
		}
	}
	
}

// Inputs New


//Inputs old
void AFpsPlayer::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}

void AFpsPlayer::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}

void AFpsPlayer::LookUp(float Value)
{
	AddControllerPitchInput(Value * MouseSensitivityPitch);
}

void AFpsPlayer::TurnRight(float Value)
{
	AddControllerYawInput(Value * MouseSensitivity);
}

void AFpsPlayer::PlayerJump()
{
	Jump();
}
//End Inputs
