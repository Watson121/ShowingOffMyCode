// Fill out your copyright notice in the Description page of Project Settings.


#include "Clock.h"
#include "FinalReportSystem.h"
#include "PlayerCharacter.h"
#include "StrikeSystemInstance.h"

// Sets default values
AClock::AClock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AClock::BeginPlay()
{
	//gameInstance = Cast<UStrikeSystemInstance>(GetGameInstance());

	//for (TActorIterator<AFinalReportSystem> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
	//	finalReportSystem = *ActorItr;
	//}

	//for (TActorIterator<APlayerCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
	//	player = *ActorItr;
	//}
	
	//SetTime();
	Super::BeginPlay();
	
}

// Called every frame
void AClock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AClock::SetTime()
{
	gameInstance = Cast<UStrikeSystemInstance>(GetGameInstance());

	for (TActorIterator<AFinalReportSystem> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		finalReportSystem = *ActorItr;
	}

	for (TActorIterator<APlayerCharacter> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		player = *ActorItr;
	}

	if (gameInstance) {
		switch (gameInstance->currentGameMode)
		{
			/*Depending on what game model the player chooses, the player will get a certain amount of time*/
		case EGameMode::GAMEMODE_Tutorial:
			minutes = 5;
			seconds = 0;
			break;
		case EGameMode::GAMEMODE_Story:
			minutes = 3;
			seconds = 0;
			break;
		case EGameMode::GAMEMODE_TimeTrial:
			
			/*Depending on the difficulty that the play chooses, the amount of time that the player gets will be different*/

			switch (gameInstance->difficultLevel) {
			case EDifficulties::DIFFICULTY_easy:
				minutes = 5;
				seconds = 0;
				break;
			case EDifficulties::DIFFICULTY_medium:
				minutes = 3;
				seconds = 0;
				break;
			case EDifficulties::DIFFICULTY_hard:
				minutes = 2;
				seconds = 0;
				break;
			default:
				minutes = 3;
				seconds = 0;
				break;
			}
			break;
		default:
			minutes = 3;
			seconds = 0;
			break;
		}
	}
}



