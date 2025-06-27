// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 


#include "Blueprints/WeaponPickup.h"

#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWeaponPickup::AWeaponPickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootMeshComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootMeshComponent;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("InteractableMeshComponent"));
	SkeletalMeshComponent->SetCollisionProfileName(FName("BlockAllDynamic")); //In the normal mesh it's not necessary, but in the SkeletalMesh it is, as far as I can see...
	SkeletalMeshComponent->SetupAttachment(RootMeshComponent);

	BoxTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxTrigger"));
	BoxTrigger->SetupAttachment(RootMeshComponent);

	InteractableWidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractableWidgetComponent"));
	InteractableWidgetComponent->SetupAttachment(RootMeshComponent);

}

// Called when the game starts or when spawned
void AWeaponPickup::BeginPlay()
{
	Super::BeginPlay();
	
}

void AWeaponPickup::PlayerInteract_Implementation()
{
	IFpsInterface::PlayerInteract_Implementation();
	if (IFpsInterface* ImplementInterface = Cast<IFpsInterface>(this))
	{
		ImplementInterface->Execute_InternalInteract(this);
	}
	
	if (BeepSoundPickup)
	{
		UGameplayStatics::PlaySound2D(this, BeepSoundPickup);
	}
}

void AWeaponPickup::ShowMessage_Implementation()
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

void AWeaponPickup::HideMessage_Implementation()
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
void AWeaponPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

