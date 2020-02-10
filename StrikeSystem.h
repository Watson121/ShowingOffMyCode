// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StrikeSystem.generated.h"

class UStrikeSystemInstance;

UCLASS()
class THANKYOUFORSERVICE_API AStrikeSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStrikeSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int GetNumberOfStrikes();
	UFUNCTION(BlueprintCallable)
	void SetNumberOfStrikes();

private:

		int numberOfStrikes;
		UStrikeSystemInstance* gameInstance;
};
