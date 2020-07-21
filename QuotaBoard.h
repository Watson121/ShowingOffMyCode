// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Math/UnrealMathUtility.h"
#include "EngineUtils.h"
#include "Vector.h"
#include "Components\StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "QuotaBoard.generated.h"

class UStrikeSystemInstance;

UCLASS()
class THANKYOUFORSERVICE_API AQuotaBoard : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AQuotaBoard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetQuotaNumber();
	void SetNumberOfPackagesSorted();
	void SetNumberOfPackagesSortedSuccessfully();
	void SetHasQuotaBeenMet();
	
	UFUNCTION(BlueprintCallable)
	int GetQuotaNumber();
	UFUNCTION(BlueprintCallable)
	int GetNumberOfPackagesSorted();
	UFUNCTION(BlueprintCallable)
	int GetNumberOfPackagesSortedSuccessfully();
	UFUNCTION(BlueprintCallable)
	bool GetQuotaHasBeenMet();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int quotaNumber;
private:


	int numberOfPackagesSorted;
	int numberOfPackagesSortedSuccesfully;
	bool hasQuotaBeenMet;
	UStrikeSystemInstance* gameInstance;



};
