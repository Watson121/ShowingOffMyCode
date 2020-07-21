// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Array.h"
#include "Engine\World.h"
#include "EngineUtils.h"
#include "Components\StaticMeshComponent.h"
#include "Components\TextRenderComponent.h"
#include "Components\DecalComponent.h"
#include "Materials\Material.h"
#include "Text.h"
#include "Engine\Font.h"
#include "BoxCreator.generated.h"

UCLASS()
class THANKYOUFORSERVICE_API ABoxCreator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxCreator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void BoxCreation();

#pragma region Setters
	UFUNCTION(BlueprintCallable)
		void SetTypeIndex(int index);
#pragma endregion

#pragma region Getters
	UFUNCTION(BlueprintCallable)
		FString GetBoxType();
	UFUNCTION(BlueprintCallable)
		int GetTypeIndex();
	UFUNCTION(BlueprintCallable)
		TArray<FString> GetBoxTypes();
#pragma endregion

	UFUNCTION(BlueprintCallable)
		void IncreaseTypeIndex();
	UFUNCTION(BlueprintCallable)
		void DecreaseTypeIndex();



private:

	void SettingCollisoins();
	
	FString boxType;	//Stores box type string that will be used for the text componenet
	int typeIndex;		//The type index which will be used to search through the array

	//Array of different box Types
	TArray<FString> boxTypes;



};
