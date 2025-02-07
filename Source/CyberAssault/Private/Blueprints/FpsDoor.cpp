// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 


#include "Blueprints/FpsDoor.h"

#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"

// Sets default values
AFpsDoor::AFpsDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Scene Component
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;
	// Door Mesh
	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(Root);

	// Box Collision
	DoorTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorTrigger"));
	DoorTrigger->SetupAttachment(Root);

	// Timeline
	DoorTimeline = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeline"));
	
}

// Called when the game starts or when spawned
void AFpsDoor::BeginPlay()
{
	Super::BeginPlay();

	DoorInitialLocation = GetActorLocation();
	DoorFinalLocation = DoorInitialLocation + FVector(0.f, 0.f, DoorOpenZ);
	
}

// Called every frame
void AFpsDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

