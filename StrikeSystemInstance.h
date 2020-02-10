// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "StrikeSystemInstance.generated.h"

/**
 * 
 */
UCLASS()
class THANKYOUFORSERVICE_API UStrikeSystemInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UStrikeSystemInstance(const FObjectInitializer& ObjectInitializer);

#pragma region Final Report System
	int numberOfPackagesSorted;
	int numberOfPackagesSuccesfullySorted;
	int numberOfStrikes;
	int finalScore;
	bool quotaMet;
#pragma endregion







};
