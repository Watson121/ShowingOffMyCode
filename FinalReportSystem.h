// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/UnrealMathUtility.h"
#include "EngineUtils.h"
#include "Vector.h"
#include "Components\StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FinalReportSystem.generated.h"

class AQuotaBoard;
class AStrikeSystem;
class UStrikeSystemInstance;

UCLASS()
class THANKYOUFORSERVICE_API AFinalReportSystem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFinalReportSystem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetNumberOfPackagesSorted();
	UFUNCTION(BlueprintCallable)
	void SetNumberOfPackagesSortedSuccesfully();
	UFUNCTION(BlueprintCallable)
	void SetNumberOfStrikes();
	UFUNCTION(BlueprintCallable)
	void CalculateFinalScore();
	UFUNCTION(BlueprintCallable)
	void SetQuotaMet();

	UFUNCTION(BlueprintCallable)
		int GetNumberOfPackagesSorted();
	UFUNCTION(BlueprintCallable)
		int GetNumberOfSuccesfulPackages();
	UFUNCTION(BlueprintCallable)
		int GetNumberOfStrikes();
	UFUNCTION(BlueprintCallable)
		int GetFinalScore();
	UFUNCTION(BlueprintCallable)
		bool GetQuotaMet();

private:

		int numberOfPackagesSorted;
		int numberOfPackagesSuccesfullySorted;
		int numberOfStrikes;
		int finalScore;
		bool quotaMet;

		bool calculationCompleted;

		AQuotaBoard* quotaBoard;
		AStrikeSystem* strikeSystem;
		UStrikeSystemInstance* systemInstance;
		

};
