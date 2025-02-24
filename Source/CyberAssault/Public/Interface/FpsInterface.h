// RIGHTS RESERVED FOR FIXNIT IN THE DEVELOPMENT OF THIS VIDEOGAME. 

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FpsInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UFpsInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class CYBERASSAULT_API IFpsInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PlayerInteract();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void InternalInteract();
};
