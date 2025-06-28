// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FpsPlayer.generated.h"

class AWeaponPickup;
class USpringArmComponent;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;

UCLASS()
class CYBERASSAULT_API AFpsPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFpsPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "IMC")
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IMC")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IMC")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IMC")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "IMC")
	UInputAction* InteractAction;

	UFUNCTION()
	void MoveEnhancedInput(const FInputActionValue& Value);

	UFUNCTION()
	void LookEnhancedInput(const FInputActionValue& Value);

	UFUNCTION()
	void InteractEnhancedInput(const FInputActionValue& Value);

	UPROPERTY()
	AWeaponPickup* WeaponSkeletalMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<AWeaponPickup> WeaponClass;
	
private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* CameraComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* PlayerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Player")
	float MouseSensitivityYaw = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Player")
	float MouseSensitivityPitch = 1.f;

	// Line Trace
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "Player")
	float LineTraceDistance = 300.f;

	UFUNCTION()
	void LineTrace();

	FHitResult LineTraceHitResult;

	UFUNCTION()
	void PlayerShowMessage();

	UFUNCTION()
	void PlayerHideShowMessage();

	UPROPERTY()
	AActor* CachedHitActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void SpawnWeapon();

};
