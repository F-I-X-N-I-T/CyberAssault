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

	DoorInitialLocation = DoorMesh->GetRelativeLocation();
	DoorFinalLocation = DoorInitialLocation + FVector(0.f, 0.f, DoorOpenZ);

	DoorTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFpsDoor::OnDoorBeginOverlap);
	DoorTrigger->OnComponentEndOverlap.AddDynamic(this, &AFpsDoor::OnDoorEndOverlap);
	
	//Binding Function
	if (CurveFloat)
	{
		FOnTimelineFloat UpdateFunction;
		UpdateFunction.BindUFunction(this, FName("UpdateDoorLocation"));

		DoorTimeline->AddInterpFloat(CurveFloat, UpdateFunction);
		DoorTimeline->SetLooping(false);
	}
	
}

void AFpsDoor::UpdateDoorLocation(float Value)
{
	FVector NewLocation = FMath::Lerp(DoorInitialLocation, DoorFinalLocation, Value);
	if (DoorMesh)
	{
		DoorMesh->SetRelativeLocation(NewLocation);
	}
}

void AFpsDoor::OnDoorBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->ActorHasTag("Player1"))
	{
		DoorTimeline->Play();
	}
}

void AFpsDoor::OnDoorEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->ActorHasTag("Player1"))
	{
		DoorTimeline->Reverse();
	}
}

// Called every frame
void AFpsDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DoorTimeline->TickComponent(DeltaTime, ELevelTick::LEVELTICK_TimeOnly, nullptr);

}

