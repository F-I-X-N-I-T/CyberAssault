// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 


#include "Blueprints/FpsKeyPad.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Player/FpsPlayer.h"

// Sets default values
AFpsKeyPad::AFpsKeyPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;
	
	KeyPadMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("KeyPadMesh"));
	KeyPadMesh->SetupAttachment(RootScene);

	KeyPadTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyPadTrigger"));
	KeyPadTrigger->SetupAttachment(RootScene);

	KeyPadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("KeyPadWidget"));
	KeyPadWidget->SetupAttachment(RootScene);
	

}

// Called when the game starts or when spawned
void AFpsKeyPad::BeginPlay()
{
	Super::BeginPlay();
	//Binding Functions box collision
	KeyPadTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFpsKeyPad::OnKeyPadBeginOverlap);
	KeyPadTrigger->OnComponentEndOverlap.AddDynamic(this, &AFpsKeyPad::OnKeyPadEndOverlap);
	KeyPadWidget->SetVisibility(false);
	
}

void AFpsKeyPad::OnKeyPadBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFpsPlayer* OverlapActor = Cast<AFpsPlayer>(OtherActor);
	if (OverlapActor)
	{
		KeyPadWidget->SetVisibility(true);
	}
}

void AFpsKeyPad::OnKeyPadEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFpsPlayer* OverlapActor = Cast<AFpsPlayer>(OtherActor);
	if (OverlapActor)
	{
		KeyPadWidget->SetVisibility(false);
	}
}

// Called every frame
void AFpsKeyPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

