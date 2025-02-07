// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsDoor.generated.h"

class UTimelineComponent;
class UBoxComponent;

UCLASS()
class CYBERASSAULT_API AFpsDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFpsDoor();

	UPROPERTY()
	UTimelineComponent* DoorTimeline;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DoorOpenZ = 350.f;

private:

	//Variables
	UPROPERTY()
	FVector DoorInitialLocation;
	
	UPROPERTY()
	FVector DoorFinalLocation;
	//End Variables

	//Functions
	UFUNCTION()
	void UpdateDoorLocation(float Value);
	
	//End Functions

	//Components
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* DoorTrigger;
	//End Components

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
