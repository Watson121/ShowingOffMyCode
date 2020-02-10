// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestinationStamp.generated.h"

UCLASS()
class THANKYOUFORSERVICE_API ADestinationStamp : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestinationStamp();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<FString> destinationCities;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString currentCity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int cityIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool pickedUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString currentHand;
};
