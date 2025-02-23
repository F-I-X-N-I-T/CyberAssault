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

void AFpsKeyPad::PlayerInteract_Implementation()
{
	IFpsInterface::PlayerInteract_Implementation();
	DoorIsOpenedFunction();
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
		UUserWidget* Widgetbp = KeyPadWidget->GetUserWidgetObject();
		if (Widgetbp)
		{
			UFunction* ShowText = Widgetbp->FindFunction(FName("ShowText"));
			if (ShowText)
			{
				Widgetbp->ProcessEvent(ShowText, nullptr);
				KeyPadWidget->SetVisibility(true);
			}
		}
	}
}

void AFpsKeyPad::OnKeyPadEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFpsPlayer* OverlapActor = Cast<AFpsPlayer>(OtherActor);
	if (OverlapActor)
	{
		UUserWidget* Widgetbp = KeyPadWidget->GetUserWidgetObject();
		if (Widgetbp)
		{
			UFunction* HideText = Widgetbp->FindFunction(FName("HideText"));
			if (HideText)
			{
				Widgetbp->ProcessEvent(HideText, nullptr);
			}
		}
	}
}

void AFpsKeyPad::DoorIsOpenedFunction()
{
	bDoorIsOpened = true;
}

// Called every frame
void AFpsKeyPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

