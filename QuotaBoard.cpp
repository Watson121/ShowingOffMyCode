// Fill out your copyright notice in the Description page of Project Settings.


#include "QuotaBoard.h"
#include "StrikeSystemInstance.h"

// Sets default values
AQuotaBoard::AQuotaBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AQuotaBoard::BeginPlay()
{
	
	//SetQuotaNumber();

	Super::BeginPlay();
}

// Called every frame
void AQuotaBoard::Tick(float DeltaTime)
{
	gameInstance->numberOfPackagesSorted = numberOfPackagesSorted;
	gameInstance->numberOfPackagesSuccesfullySorted = numberOfPackagesSortedSuccesfully;
	gameInstance->quotaMet = hasQuotaBeenMet;


	Super::Tick(DeltaTime);
}

#pragma region Setters
void AQuotaBoard::SetQuotaNumber()
{
	//Setting the quota number with a random range
	
	int num1, num2;

	gameInstance = Cast<UStrikeSystemInstance>(GetGameInstance());

	if (gameInstance) {
		switch (gameInstance->currentGameMode) {

		case EGameMode::GAMEMODE_TimeTrial:
			switch (gameInstance->difficultLevel)
			{
			case EDifficulties::DIFFICULTY_easy:
				num1 = 5;
				num2 = 10;
				break;
			case EDifficulties::DIFFICULTY_medium:
				num1 = 10;
				num2 = 20;
				break;
			case EDifficulties::DIFFICULTY_hard:
				num1 = 20;
				num2 = 30;
				break;
			default:
				num1 = 10;
				num2 = 20;
				break;
			}
			break;
		case EGameMode::GAMEMODE_Story:
			switch (gameInstance->storyDay) {
			case EDay::DAY_One:
				num1 = 5;
				num2 = 10;
				break;
			case EDay::DAY_Two:
				num1 = 10;
				num2 = 20;
				break;
			case EDay::DAY_Three:
				num1 = 20;
				num2 = 30;
				break;
			case EDay::DAY_Four:
				num1 = 30;
				num2 = 40;
				break;
			}
			break;
		case EGameMode::GAMEMODE_Tutorial:
			num1 = 3;
			num2 = 5;
			break;
		default:
			num1 = 20;
			num2 = 30;
		}
	}
	
	if((num1) && (num2))
		quotaNumber = FMath::RandRange(num1, num2);
	else
		quotaNumber = FMath::RandRange(20, 30);

}

void AQuotaBoard::SetNumberOfPackagesSorted()
{
	//Increase Number of Packages Sorted
	numberOfPackagesSorted++;
}

void AQuotaBoard::SetNumberOfPackagesSortedSuccessfully()
{
	//Increase Number of Packages Succesfully Sorted
	numberOfPackagesSortedSuccesfully++;
}

void AQuotaBoard::SetHasQuotaBeenMet()
{
	//Sets that the quota been met to true
	hasQuotaBeenMet = true;
}


#pragma endregion

#pragma region Getters
int AQuotaBoard::GetNumberOfPackagesSorted()
{
	return numberOfPackagesSorted;
}

int AQuotaBoard::GetNumberOfPackagesSortedSuccessfully()
{
	return numberOfPackagesSortedSuccesfully;
}

bool AQuotaBoard::GetQuotaHasBeenMet()
{
	return hasQuotaBeenMet;
}

int AQuotaBoard::GetQuotaNumber()
{
	return quotaNumber;
}
#pragma endregion




