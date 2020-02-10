// Fill out your copyright notice in the Description page of Project Settings.


#include "StrikeSystem.h"
#include "StrikeSystemInstance.h"

// Sets default values
AStrikeSystem::AStrikeSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AStrikeSystem::BeginPlay()
{

	gameInstance = Cast<UStrikeSystemInstance>(GetGameInstance());

	Super::BeginPlay();
	
}

// Called every frame
void AStrikeSystem::Tick(float DeltaTime)
{
	if (gameInstance) {
		gameInstance->numberOfStrikes = numberOfStrikes;
	}

	Super::Tick(DeltaTime);

}

int AStrikeSystem::GetNumberOfStrikes()
{
	return numberOfStrikes;
}

void AStrikeSystem::SetNumberOfStrikes()
{
	numberOfStrikes++;
}

