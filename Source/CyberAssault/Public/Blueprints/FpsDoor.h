// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interface/FpsInterface.h"
#include "FpsDoor.generated.h"

class UTimelineComponent;
class UBoxComponent;

UCLASS()
class CYBERASSAULT_API AFpsDoor : public AActor, public IFpsInterface
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bIsOpenDoor = false;

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

	UFUNCTION()
	void OnDoorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnDoorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	//End Functions

	//Components
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* DoorTrigger;
	//End Components

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
