// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Clock.generated.h"

class AFinalReportSystem;
class APlayerCharacter;
class UStrikeSystemInstance;

UCLASS()
class THANKYOUFORSERVICE_API AClock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AClock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int currentDay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int minutes;			//This will double as hours for the storymode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int seconds;			//This will double as minutes for the storymode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool timeUp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool countdown;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString gameMode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AFinalReportSystem* finalReportSystem;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerCharacter* player;

	UFUNCTION(BlueprintCallable)
		void SetTime();

private:

	UStrikeSystemInstance* gameInstance;
};
