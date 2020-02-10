// Fill out your copyright notice in the Description page of Project Settings.


#include "FinalReportSystem.h"
#include "QuotaBoard.h"
#include "StrikeSystem.h"
#include "StrikeSystemInstance.h"

// Sets default values
AFinalReportSystem::AFinalReportSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	numberOfPackagesSorted = 0; 
	numberOfPackagesSuccesfullySorted = 0;
	numberOfStrikes = 0;
	quotaMet = false;
	finalScore = 0;

	calculationCompleted = false;

}

// Called when the game starts or when spawned
void AFinalReportSystem::BeginPlay()
{

	for (TActorIterator<AQuotaBoard> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		quotaBoard = *ActorItr;
	}

	for (TActorIterator<AStrikeSystem> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		strikeSystem = *ActorItr;
	}

	systemInstance = Cast<UStrikeSystemInstance>(GetGameInstance());

	CalculateFinalScore();

	Super::BeginPlay();
}

// Called every frame
void AFinalReportSystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFinalReportSystem::CalculateFinalScore()
{
	int packageScore = 500;
	int	packageSortedScore = 1000;
	int quotaScore = 10000;
	int noStrikeScore = 10000;
	int strikeScore = 1000;


	if (systemInstance) {
		SetNumberOfPackagesSorted();
		SetNumberOfPackagesSortedSuccesfully();
		SetNumberOfStrikes();
		SetQuotaMet();
	}


		if (quotaMet == true) {
			finalScore = finalScore + quotaScore;
			packageScore = 750;
			packageSortedScore = 1500;

			finalScore = finalScore + (packageScore * numberOfPackagesSorted) + (packageSortedScore  * numberOfPackagesSuccesfullySorted);
		}
		else if (quotaMet == false) {
			packageScore = 500;
			packageSortedScore = 1000;

			finalScore = finalScore + (packageScore * numberOfPackagesSorted) + (packageSortedScore  * numberOfPackagesSuccesfullySorted);
		}

		if (numberOfStrikes == 0) {
			finalScore = finalScore + noStrikeScore;
		}
		else if (numberOfStrikes > 0) {
			finalScore = finalScore - (strikeScore * numberOfStrikes);
		}


}



#pragma region Setters
void AFinalReportSystem::SetNumberOfPackagesSorted()
{
	numberOfPackagesSorted = systemInstance->numberOfPackagesSorted;
}

void AFinalReportSystem::SetNumberOfPackagesSortedSuccesfully()
{
	numberOfPackagesSuccesfullySorted = systemInstance->numberOfPackagesSuccesfullySorted;
}

void AFinalReportSystem::SetNumberOfStrikes()
{
	numberOfStrikes = systemInstance->numberOfStrikes;
}

void AFinalReportSystem::SetQuotaMet()
{
	quotaMet = systemInstance->quotaMet;
}
#pragma endregion

#pragma region Getters
int AFinalReportSystem::GetNumberOfPackagesSorted()
{
	return numberOfPackagesSorted;
}

int AFinalReportSystem::GetNumberOfSuccesfulPackages()
{
	return numberOfPackagesSuccesfullySorted;
}

int AFinalReportSystem::GetNumberOfStrikes()
{
	return numberOfStrikes;
}

int AFinalReportSystem::GetFinalScore()
{
	return finalScore;
}

bool AFinalReportSystem::GetQuotaMet()
{
	return quotaMet;
}

#pragma endregion



