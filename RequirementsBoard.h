// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineUtils.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RequirementsBoard.generated.h"

class AThePackage;

UCLASS()
class THANKYOUFORSERVICE_API ARequirementsBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ARequirementsBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetDestinationCity(FString city);
	void SetChuteColour(FString colour);
	void SetBoxType(FString type);
	void SetBoxSize(FString size);


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString destinationCity;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString chuteColour;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString typeOfBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString sizeOfBox;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AThePackage* package;
	
private:




};
