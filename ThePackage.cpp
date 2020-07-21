// Fill out your copyright notice in the Description page of Project Settings.
#include "ThePackage.h"
#include "RequirementsBoard.h"
#include "StrikeSystem.h"
#include "FinalReportSystem.h"
#include "BoxTypeAndSize.h"
#include "QuotaBoard.h"
#include "BoxType1.h"
#include "BoxType2.h"
#include "BoxType3.h"
#include "EnumHolder.h"

using namespace PackageParameters;



// Sets default values
AThePackage::AThePackage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	packageMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Package"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> vaseMeshObj(TEXT("StaticMesh'/Game/8_Models/Vase.Vase'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> consoleMeshObj(TEXT("StaticMesh'/Game/8_Models/Console.Console'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> toyMeshObj(TEXT("StaticMesh'/Game/8_Models/Toy.Toy'"));

	if (vaseMeshObj.Object)vaseMesh = vaseMeshObj.Object;
	if (consoleMeshObj.Object)consoleMesh = consoleMeshObj.Object;
	if (toyMeshObj.Object)toyMesh = toyMeshObj.Object;

	if (packageMeshComponent) { packageMeshComponent->SetStaticMesh(consoleMesh); }

	RootComponent = packageMeshComponent;

	numberOfRequirementsCorrect = 0;
	pickedUp = false;
	highlightActive = false;

}

// Called when the game starts or when spawned
void AThePackage::BeginPlay()
{
	packageRequirements = new FPackageRequirement();
	packageParameters = new FPackageInputs();

	SetRequirements();

	Super::BeginPlay();
}

// Called every frame
void AThePackage::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AThePackage::GetPickedUp()
{
	return pickedUp;
}

bool AThePackage::GetHighlightActive()
{
	return highlightActive;
}

int AThePackage::GetNumberOfRequirements()
{
	return numberOfRequirementsCorrect;
}

void AThePackage::SetRequirements()
{
	if (packageRequirements) {

		UE_LOG(LogTemp, Warning, TEXT("Package Requirements initlaized"));

		packageRequirements->SetPackageType(static_cast<EPackageTypes>(rand() % PACKAGE_Vase));

		switch (packageRequirements->GetPackageType()) {
		case EPackageTypes::PACKAGE_Console:
			packageRequirements->SetBoxType(EBoxTypes::BTYPE_BoxType2);
			break;
		case EPackageTypes::PACKAGE_Toy:
			packageRequirements->SetBoxType(EBoxTypes::BTYPE_BoxType1);
			break;
		case EPackageTypes::PACKAGE_Vase:
			packageRequirements->SetBoxType(EBoxTypes::BTYPE_BoxType3);
			break;
		}

		packageRequirements->SetChuteColour(static_cast<EChuteColour>(rand() % COLOUR_BLUE));
		packageRequirements->SetDestiantionCity(static_cast<EDestinationCities>(rand() % CITY_Liverpool));

		UE_LOG(LogTemp, Warning, TEXT("The Requirements for this package are: "));
		UE_LOG(LogTemp, Warning, TEXT("Text, %d"), packageRequirements->GetPackageType());
		UE_LOG(LogTemp, Warning, TEXT("Text, %d"), packageRequirements->GetDestinationCity());
		UE_LOG(LogTemp, Warning, TEXT("Text, %d"), packageRequirements->GetBoxType());
		UE_LOG(LogTemp, Warning, TEXT("Text, %d"), packageRequirements->GetChuteColour());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Package Requirements not initlaized"));
	}
}

void AThePackage::CallRequirmentsBoard()
{
}







