// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/FpsInterface.h"
#include "FpsKeyPad.generated.h"

class UBoxComponent;
class UWidgetComponent;

UCLASS()
class CYBERASSAULT_API AFpsKeyPad : public AActor, public IFpsInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFpsKeyPad();

	//Interface
	virtual void PlayerInteract_Implementation() override;
	virtual void InternalInteract_Implementation() override;
	virtual void ShowMessage_Implementation() override;
	virtual void HideMessage_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bDoorIsOpened = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	USoundBase* BeepSoundKeyPad;

	//Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootScene;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* KeyPadMesh;

	//Box Collision
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	//UBoxComponent* KeyPadTrigger;

	//Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* KeyPadWidget;

	UFUNCTION()
	void DoorIsOpenedFunction();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
