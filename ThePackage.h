// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EnumHolder.h"

#include "Math/UnrealMathUtility.h"
#include "EngineUtils.h"
#include "Vector.h"
#include "Components\StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThePackage.generated.h"


class ARequirementsBoard;
class AStrikeSystem;
class AFinalReportSystem;
class ABoxTypeAndSize; 
class AQuotaBoard;
class ABoxType1;
class ABoxType2;
class ABoxType3;
class EnumHolder;

USTRUCT(Blueprintable) /*Struct that is responsible for setting and getting the pacakge requirements*/
struct FPackageRequirement {

	GENERATED_BODY()

	FPackageRequirement() : packageType(), destinationCity(), boxType(), chuteColour() {}

public:

#pragma region GETTERS
	PackageParameters::EPackageTypes GetPackageType() { return packageType; }
	PackageParameters::EDestinationCities GetDestinationCity() { return destinationCity; }
	PackageParameters::EBoxTypes GetBoxType() { return boxType; }
	PackageParameters::EChuteColour GetChuteColour() { return chuteColour; }
#pragma endregion

#pragma region SETTERS
	void SetPackageType(TEnumAsByte<PackageParameters::EPackageTypes> type) { packageType = type; }
	void SetDestiantionCity(TEnumAsByte<PackageParameters::EDestinationCities>  city) { destinationCity = city; }
	void SetBoxType(TEnumAsByte<PackageParameters::EBoxTypes> type) { boxType = type; }
	void SetChuteColour(TEnumAsByte<PackageParameters::EChuteColour> colour) { chuteColour = colour; }
#pragma endregion

private:

	TEnumAsByte<PackageParameters::EPackageTypes> packageType;
	TEnumAsByte<PackageParameters::EDestinationCities> destinationCity;
	TEnumAsByte<PackageParameters::EBoxTypes> boxType;
	TEnumAsByte<PackageParameters::EChuteColour> chuteColour;

};

USTRUCT() /*Struct that is responsible for setting and getting the pacakge inputs*/
struct FPackageInputs {

	GENERATED_BODY()

		FPackageInputs() : destinationCity(), boxType(), chuteColour() {}
	

public:

#pragma region GETTERS
	PackageParameters::EDestinationCities GetDestinationCity() { return destinationCity; }
	PackageParameters::EBoxTypes GetBoxType() { return boxType; }
	PackageParameters::EChuteColour GetChuteColour() { return chuteColour; }
#pragma endregion

#pragma region SETTERS
	void SetDestiantionCity(TEnumAsByte<PackageParameters::EDestinationCities> city) { destinationCity = city; }
	void SetBoxType(TEnumAsByte<PackageParameters::EBoxTypes> type) { boxType = type; }
	void SetChuteColour(TEnumAsByte<PackageParameters::EChuteColour> colour) { chuteColour = colour; }
#pragma endregion

private:

	TEnumAsByte<PackageParameters::EDestinationCities> destinationCity;
	TEnumAsByte<PackageParameters::EBoxTypes> boxType;
	TEnumAsByte<PackageParameters::EChuteColour> chuteColour;

};


UCLASS()
class THANKYOUFORSERVICE_API AThePackage : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AThePackage();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	FPackageRequirement* packageRequirements;
	FPackageInputs* packageParameters;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	bool GetPickedUp();
	bool GetHighlightActive();
	int GetNumberOfRequirements();

private:

	UStaticMeshComponent* packageMeshComponent;
	UStaticMesh* packageMesh;
	UStaticMesh* vaseMesh;
	UStaticMesh* consoleMesh;
	UStaticMesh* toyMesh;

	bool pickedUp;
	bool highlightActive;
	int numberOfRequirementsCorrect;

	void SetRequirements();
	void CallRequirmentsBoard();
};
