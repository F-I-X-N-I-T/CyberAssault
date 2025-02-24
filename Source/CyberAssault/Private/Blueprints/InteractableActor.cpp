// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 


#include "Blueprints/InteractableActor.h"

#include "Blueprints/FpsKeyPad.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Player/FpsPlayer.h"

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

	//Binding
	BoxTrigger->OnComponentBeginOverlap.AddDynamic(this, &AInteractableActor::OnInteractableBeginOverlap);
	BoxTrigger->OnComponentEndOverlap.AddDynamic(this, &AInteractableActor::OnInteractableEndOverlap);

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
	}
}

void AInteractableActor::OnInteractableBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFpsPlayer* OverlapActor = Cast<AFpsPlayer>(OtherActor);
	if (OverlapActor)
	{
		UUserWidget* Widgetbp = InteractableWidgetComponent->GetUserWidgetObject();
		if (Widgetbp)
		{
			UFunction* ShowText = Widgetbp->FindFunction(FName("ShowText"));
			if (ShowText)
			{
				Widgetbp->ProcessEvent(ShowText, nullptr);
				InteractableWidgetComponent->SetVisibility(true);
			}
		}
	}
}

void AInteractableActor::OnInteractableEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AFpsPlayer* OverlapActor = Cast<AFpsPlayer>(OtherActor);
	if (OverlapActor)
	{
		UUserWidget* Widgetbp = InteractableWidgetComponent->GetUserWidgetObject();
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


// Called every frame
void AInteractableActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

