// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Containers\EnumAsByte.h"
#include "StrikeSystemInstance.generated.h"

UENUM(BlueprintType)
enum EDifficulties {
	DIFFICULTY_easy,
	DIFFICULTY_medium,
	DIFFICULTY_hard
};

UENUM(BlueprintType)
enum ELevel {
	LEVEL_MainMenu,
	LEVEL_TimeTrial,
	LEVEL_FinalPointsRoom,
};

UENUM(BlueprintType)
enum EGameMode {
	GAMEMODE_Story,
	GAMEMODE_TimeTrial,
	GAMEMODE_Tutorial
};

UENUM(BlueprintType)
enum EDay {
	DAY_One,
	DAY_Two,
	DAY_Three,
	DAY_Four,
	DAY_Death
};


UCLASS()
class THANKYOUFORSERVICE_API UStrikeSystemInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

	UStrikeSystemInstance(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EDifficulties> difficultLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ELevel> currentLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EGameMode> currentGameMode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EDay> storyDay;

#pragma region Final Report System
	int numberOfPackagesSorted;
	int numberOfPackagesSuccesfullySorted;
	int numberOfStrikes;
	int finalScore;
	bool quotaMet;
#pragma endregion
};
