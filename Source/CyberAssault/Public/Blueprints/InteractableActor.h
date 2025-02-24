// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/FpsInterface.h"
#include "InteractableActor.generated.h"

class AFpsKeyPad;
class UWidgetComponent;
class UBoxComponent;

UCLASS()
class CYBERASSAULT_API AInteractableActor : public AActor, public IFpsInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInteractableActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Interface
	virtual void PlayerInteract_Implementation() override;
	virtual void ShowMessage_Implementation() override;

	// ref to keypad public
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AFpsKeyPad* KeyPadRef;

private:
	//Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* InteractableMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* BoxTrigger;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* InteractableWidgetComponent;

	//Functions
	UFUNCTION()
	void OnInteractableEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
