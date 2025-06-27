// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/FpsInterface.h"
#include "WeaponPickup.generated.h"

class UWidgetComponent;
class UBoxComponent;

UCLASS()
class CYBERASSAULT_API AWeaponPickup : public AActor, public IFpsInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Interface
	virtual void PlayerInteract_Implementation() override;
	virtual void ShowMessage_Implementation() override;
	virtual void HideMessage_Implementation() override;

private:
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* SkeletalMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* InteractableWidgetComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	USoundBase* BeepSoundPickup;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
