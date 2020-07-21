// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Sound\SoundCue.h"
#include "EngineUtils.h"
#include "Components\StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials\Material.h"
#include "Kismet/GameplayStatics.h"
#include "StrikeSystem.generated.h"

class UStrikeSystemInstance;

UCLASS()
class THANKYOUFORSERVICE_API AStrikeSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AStrikeSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		int GetNumberOfStrikes();
	UFUNCTION(BlueprintCallable)
		void SetNumberOfStrikes();
	UFUNCTION(BlueprintCallable)
		void PlayStrikeSound();

		UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int numberOfStrikes;

private:

		UStrikeSystemInstance* gameInstance;
		UStaticMeshComponent* clockBase;
		UStaticMeshComponent* strikeOne;
		UStaticMeshComponent* strikeTwo;
		UStaticMeshComponent* strikeThree;

		UStaticMesh* clockModel;
		UStaticMesh* strikeModel;
		USoundCue* strikeSound;

		UMaterialInterface* mLightRed;

};
