// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Chute.generated.h"

class AQuotaBoard;

UCLASS()
class THANKYOUFORSERVICE_API AChute : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChute();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int chuteNumber;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString chuteColour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AQuotaBoard* quotaBoard;
};
