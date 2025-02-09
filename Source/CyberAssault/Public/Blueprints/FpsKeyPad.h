// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FpsKeyPad.generated.h"

class UBoxComponent;
class UWidgetComponent;

UCLASS()
class CYBERASSAULT_API AFpsKeyPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFpsKeyPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	//Variables

	//Mesh
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	USceneComponent* RootScene;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* KeyPadMesh;

	//Box Collision
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UBoxComponent* KeyPadTrigger;

	//Widget
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UWidgetComponent* KeyPadWidget;

	//Overlapping
	UFUNCTION()
	void OnKeyPadBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnKeyPadEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
