// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 


#include "Blueprints/FpsKeyPad.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"
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

	//KeyPadTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("KeyPadTrigger"));
	//KeyPadTrigger->SetupAttachment(RootScene);

	KeyPadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("KeyPadWidget"));
	KeyPadWidget->SetupAttachment(RootScene);
	

}

void AFpsKeyPad::PlayerInteract_Implementation()
{
	IFpsInterface::PlayerInteract_Implementation();
	//DoorIsOpenedFunction();
	if (BeepSoundKeyPad)
	{
		UGameplayStatics::PlaySound2D(this, BeepSoundKeyPad);
	}
}

void AFpsKeyPad::InternalInteract_Implementation()
{
	IFpsInterface::InternalInteract_Implementation();
	DoorIsOpenedFunction();
}

// Called when the game starts or when spawned
void AFpsKeyPad::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFpsKeyPad::ShowMessage_Implementation()
{
	IFpsInterface::ShowMessage_Implementation();
	if (UUserWidget* Widgetbp = KeyPadWidget->GetUserWidgetObject())
	{
		if (UFunction* ShowText = Widgetbp->FindFunction(FName("ShowText")))
		{
			Widgetbp->ProcessEvent(ShowText, nullptr);
		}
	}
}

void AFpsKeyPad::HideMessage_Implementation()
{
	IFpsInterface::HideMessage_Implementation();
	IFpsInterface::HideMessage_Implementation();
	if (UUserWidget* Widgetbp = KeyPadWidget->GetUserWidgetObject())
	{
		if (UFunction* HideText = Widgetbp->FindFunction(FName("HideText")))
		{
			Widgetbp->ProcessEvent(HideText, nullptr);
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

