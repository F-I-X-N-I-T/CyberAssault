// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 


#include "Blueprints/InteractableActor.h"

#include "Blueprints/FpsKeyPad.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractableActor::AInteractableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootMeshComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootMeshComponent;

	InteractableMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InteractableMeshComponent"));
	InteractableMeshComponent->SetupAttachment(RootMeshComponent);

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxTrigger->SetupAttachment(RootMeshComponent);

	InteractableWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractableWidgetComponent"));
	InteractableWidgetComponent->SetupAttachment(RootMeshComponent);

}

// Called when the game starts or when spawned
void AInteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AInteractableActor::PlayerInteract_Implementation()
{
	IFpsInterface::PlayerInteract_Implementation();
	if (IFpsInterface* ImplementInterface = Cast<IFpsInterface>(this))
	{
		ImplementInterface->Execute_InternalInteract(KeyPadRef);
		if (BeepSoundLaptop)
		{
			UGameplayStatics::PlaySound2D(this, BeepSoundLaptop);
		}
	}
}

void AInteractableActor::ShowMessage_Implementation()
{
	IFpsInterface::ShowMessage_Implementation();
	if (UUserWidget* Widgetbp = InteractableWidgetComponent->GetUserWidgetObject())
	{
		if (UFunction* ShowText = Widgetbp->FindFunction(FName("ShowText")))
		{
			Widgetbp->ProcessEvent(ShowText, nullptr);
		}
	}
}

void AInteractableActor::HideMessage_Implementation()
{
	IFpsInterface::HideMessage_Implementation();
	if (UUserWidget* Widgetbp = InteractableWidgetComponent->GetUserWidgetObject())
	{
		if (UFunction* HideText = Widgetbp->FindFunction(FName("HideText")))
		{
			Widgetbp->ProcessEvent(HideText, nullptr);
		}
	}
}

// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

