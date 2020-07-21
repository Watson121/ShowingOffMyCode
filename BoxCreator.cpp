// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxCreator.h"
#include "BoxType1.h"
#include "BoxType2.h"
#include "BoxType3.h"

// Sets default values
ABoxCreator::ABoxCreator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABoxCreator::BeginPlay()
{
	

	

#pragma region Setting up the arrays
	//Setting up the size of the arrays
	boxTypes.SetNum(3);

	//Fills the box types array
	boxTypes[0] = "Type 1";
	boxTypes[1] = "Type 2";
	boxTypes[2] = "Type 3";

	typeIndex = 0;
#pragma endregion

	Super::BeginPlay();
	
}

// Called every frame
void ABoxCreator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABoxCreator::BoxCreation()
{
	
}

void ABoxCreator::SettingCollisoins() {

}

void ABoxCreator::IncreaseTypeIndex()
{
	if (typeIndex == 2) {
		typeIndex = 0;
	}
	else {
		if (boxTypes.IsValidIndex(typeIndex)) {
			typeIndex++;
		}
	}

}
void ABoxCreator::DecreaseTypeIndex()
{
	if (typeIndex == 0) {
		typeIndex = 2;
	}
	else {
		if (boxTypes.IsValidIndex(typeIndex)) {
			typeIndex--;
		}
	}
}


#pragma region Setters
void ABoxCreator::SetTypeIndex(int index)
{
	typeIndex = index;
}
#pragma endregion

#pragma region Getters
FString ABoxCreator::GetBoxType()
{
	return boxType;
}

int ABoxCreator::GetTypeIndex()
{
	return typeIndex;
}

TArray<FString> ABoxCreator::GetBoxTypes()
{
	return boxTypes;
}

#pragma endregion




