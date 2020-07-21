// Copyright of Adam Tedder 2020

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PickupActorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPickupActorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THANKYOUFORSERVICE_API IPickupActorInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual void Pickup(USceneComponent* AttachTo);
	virtual void Drop();


};
