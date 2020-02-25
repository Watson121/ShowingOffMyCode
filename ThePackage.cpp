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

// Sets default values
AThePackage::AThePackage()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	//Creates the Static Mesh Component 
	packageMeshComponenet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Package"));
	highlightMeshComponenet = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Highlight"));

	//Below these will search through the game files to find the correct Static Meshes.
	static ConstructorHelpers::FObjectFinder<UStaticMesh> placeholderMeshObject(TEXT("'StaticMesh'/Game/Models/PackagePlaceholder.PackagePlaceholder''"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> vaseMeshObject(TEXT("StaticMesh'/Game/Models/Vase.Vase'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> consoleMeshObject(TEXT("StaticMesh'/Game/Models/Console.Console'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> toyMeshObject(TEXT("StaticMesh'/Game/Models/Toy.Toy'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> vaseHighlightObject(TEXT("StaticMesh'/Game/Models/VaseHighlight.VaseHighlight'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> consoleHighlightObject(TEXT("StaticMesh'/Game/Models/ConsoleHighlight.ConsoleHighlight'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> toyHighlightObject(TEXT("StaticMesh'/Game/Models/ToyHighlight.ToyHighlight'"));

	//If the objects are found, then they are insilised in the mesh variables.
	placeholderMesh = placeholderMeshObject.Object;
	vaseMesh = vaseMeshObject.Object;
	consoleMesh = consoleMeshObject.Object;
	toyMesh = toyMeshObject.Object;
	vaseHighlighMesh = vaseHighlightObject.Object;
	consoleHighlightMesh = consoleHighlightObject.Object;
	toyHighlightMesh = toyHighlightObject.Object;

	//Defualt Static Mesh setting
	if (placeholderMesh) {
		packageMeshComponenet->SetStaticMesh(packageMesh);
	}

	//Sets the damage parameters
	damaged = false;
	distance = 0.0f;
	timerInt = 0.0f;
	packageSpeed = 0.0f;
	damageAmount = 0;

	numberOfRequirementsCorrect = 0;

	RootComponent = packageMeshComponenet;
	
	FVector location = GetTransform().TransformPosition(packageMeshComponenet->GetComponentLocation());
	
	highlightMeshComponenet->SetWorldLocation(FVector(location.X, location.Y, location.Z));
	highlightMeshComponenet->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	
	highlightMeshComponenet->SetVisibility(false);
}

// Called when the game starts or when spawned
void AThePackage::BeginPlay()
{
#pragma region SETTING UP THE ARRAYS
	//Below sets the sizes of each array
	destinationCities.SetNum(6);
	chuteColours.SetNum(3);
	boxTypes.SetNum(3);


	//Fills the desination cities array
	destinationCities[0] = "London";
	destinationCities[1] = "Manchester";
	destinationCities[2] = "Birmingham";
	destinationCities[3] = "Newcastle";
	destinationCities[4] = "Liverpool";
	destinationCities[5] = "Bristol";

	//Fills the Chutes Colours Array
	chuteColours[0] = "Red";
	chuteColours[1] = "Green";
	chuteColours[2] = "Blue";

	//Fills the Box Types Array
	boxTypes[0] = "Type 1";
	boxTypes[1] = "Type 2";
	boxTypes[2] = "Type 3";




#pragma endregion

#pragma region FIND THE OTHER COMPONENTS IN THE CURRENT LEVEL	
	//Find the requirement board in the current level
	for (TActorIterator<ARequirementsBoard> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		requirementsBoard = *ActorItr;
	}

	//Find the Strike System in the current level
	for (TActorIterator<AStrikeSystem> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		strikeSystem = *ActorItr;
	}

	//Find the Quota Board in the current level
	for (TActorIterator<AQuotaBoard> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		quotaBoard = *ActorItr;
	}

#pragma endregion

	SetRequirements();
	//SetPackageMesh();
	
	packageMeshComponenet->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	packageMeshComponenet->BodyInstance.SetObjectType(ECollisionChannel::ECC_GameTraceChannel3);

	//Preset Channels
	packageMeshComponenet->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	packageMeshComponenet->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Block);
	packageMeshComponenet->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Block);
	//packageMeshComponenet->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	packageMeshComponenet->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Block);
	packageMeshComponenet->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Block);
	packageMeshComponenet->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Block);
	packageMeshComponenet->SetCollisionResponseToChannel(ECC_Destructible, ECollisionResponse::ECR_Block);

	//Custom Channels
	packageMeshComponenet->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECollisionResponse::ECR_Overlap);
	packageMeshComponenet->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
	packageMeshComponenet->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);


	packageMeshComponenet->SetSimulatePhysics(true);

	Super::BeginPlay();
}

// Called every frame
void AThePackage::Tick(float DeltaTime)
{
	if (pickedUp == true) {
		CallRequirementsBoard();
	}
	
	if (highlightMeshComponenet) {
		highlightMeshComponenet->SetVisibility(highlightActive);
	}

	Super::Tick(DeltaTime);
}

void AThePackage::OnCompHit(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, bool SelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult & Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL)) {
		UE_LOG(LogTemp, Warning, TEXT("This Worked"));
		stopPoint = HitLocation;
		distance = FVector::Distance(stopPoint, dropPoint);
		whileMoving = false;
	}
}

void AThePackage::TurningOffThePhysics()
{
	packageMeshComponenet->SetSimulatePhysics(false);
}

void AThePackage::SetRequirements()
{
	int randomNumber;

#pragma region Setting the destination city Requriment
	randomNumber = FMath::RandRange(0, destinationCities.Num() - 1);

	if (randomNumber <= destinationCities.Num() - 1) {
		destinationRequirement = destinationCities[randomNumber];
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Out of bounds"));
	}
#pragma endregion

#pragma region Setting the chute colour requirement
	randomNumber = FMath::RandRange(0, chuteColours.Num() - 1);

	if (randomNumber <= chuteColours.Num() - 1) {
		chuteRequirement = chuteColours[randomNumber];
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Out of bounds"));
	}
#pragma endregion

#pragma region Setting the object name

	/*This sets the name of the object*/

	
	randomNumber = FMath::RandRange(0, 2);

	switch (randomNumber)
	{
	case EPackageTypes::PACKAGE_Toy:
		boxTypeRequirement = "Type 1";

		if (toyMesh)
			packageMeshComponenet->SetStaticMesh(toyMesh);
		
		if (toyHighlightMesh)
			highlightMeshComponenet->SetStaticMesh(toyHighlightMesh);
		break;
	case EPackageTypes::PACKAGE_Console:
		boxTypeRequirement = "Type 2";

		if (consoleMesh)
			packageMeshComponenet->SetStaticMesh(consoleMesh);
		
		if (consoleHighlightMesh)
			highlightMeshComponenet->SetStaticMesh(consoleHighlightMesh);
		break;
	case EPackageTypes::PACKAGE_Vase:
		boxTypeRequirement = "Type 3";

		if (vaseMesh)
			packageMeshComponenet->SetStaticMesh(vaseMesh);
		
		if (vaseHighlighMesh)
			highlightMeshComponenet->SetStaticMesh(vaseHighlighMesh);
		break;
	}
	
#pragma endregion


#pragma region Setting the box type requirement

	/*Depending on what the object is, this package will be assigned a certain type*/


	//randomNumber = FMath::RandRange(0, boxTypes.Num() - 1);

	//if (randomNumber <= boxTypes.Num() - 1) {
	//	boxTypeRequirement = boxTypes[randomNumber];
	//}
	//else {
	//	UE_LOG(LogTemp, Warning, TEXT("Out of bounds"));
	//}
#pragma endregion



	UE_LOG(LogTemp, Warning, TEXT("All Requirements Set"));
}

void AThePackage::SetPackageMesh()
{
	/*This function is designed to set the static mesh of the packge.*/

	if (objectName == "Vase") {
		if (vaseMesh) {
			packageMeshComponenet->SetStaticMesh(vaseMesh);
		}

		if (vaseHighlighMesh) {
			highlightMeshComponenet->SetStaticMesh(vaseHighlighMesh);
		}
	}else if (objectName == "Console") {
		if (consoleMesh) {
			packageMeshComponenet->SetStaticMesh(consoleMesh);
		}

		if (consoleHighlightMesh) {
			highlightMeshComponenet->SetStaticMesh(consoleHighlightMesh);
		}

	}else if (objectName == "Toy") {
		if (toyMesh) {
			packageMeshComponenet->SetStaticMesh(toyMesh);
		}

		if (toyHighlightMesh) {
			highlightMeshComponenet->SetStaticMesh(toyHighlightMesh);
		}
	}
}

void AThePackage::CallRequirementsBoard()
{
	//This function will send the values of the requirement variables to the reqruirement board

	requirementsBoard->SetDestinationCity(GetDestinationCityRequirement());
	requirementsBoard->SetChuteColour(GetChuteColourRequirement());
	requirementsBoard->SetBoxType(GetBoxTypeRequirement());

	UE_LOG(LogTemp, Warning, TEXT("Requirements Sent to board"));
}

void AThePackage::DestroyThis()
{
	//Destroys the object once it is no longer needed.

	UE_LOG(LogTemp, Warning, TEXT("Packaged Destroyed"));
	Destroy(this);
}

void AThePackage::RequirementCheck()
{
	//This function will check to see if the player has met the requirements
	
	//Determines if the destination city is correct or not
	if (destinationCity == destinationRequirement) {
		numberOfRequirementsCorrect++;
	}

	//Determines if the chute colour is the correct or not
	if (chuteColour == chuteRequirement) {
		numberOfRequirementsCorrect++;
	}

	//Determines if the box colour is correct or not
	if (boxType == boxTypeRequirement) {
		numberOfRequirementsCorrect++;
	}

	//Determines if the package has been badly damaged or not
	//if (damaged == false) {
	//	numberOfRequirementsCorrect++;
	//}

	//If the player does not meet five of the requirements, then they will get a strike
	if (numberOfRequirementsCorrect < 3) {
		strikeSystem->SetNumberOfStrikes();			//A Strike is sent to the strike system
		quotaBoard->SetNumberOfPackagesSorted();	//Sends a message saying a package has been sorted, but not correctly
	}
	else if (numberOfRequirementsCorrect == 3) {
		quotaBoard->SetNumberOfPackagesSorted();				//Sends a message saying that a package has been sorted
		quotaBoard->SetNumberOfPackagesSortedSuccessfully();	//Sends a message saying that a package has been sorted correctly
	}
}

bool AThePackage::DamageCheck()
{
	//This function checks if the damage is above 50 or not.

	if (damageAmount >= 50) {
		damaged = true;

		//If the damage is above 50, it will set the damage value to true which will mean the player will get a strike. 
		//This is because they have casued too much damage.
	}
	else {
		damaged = false;
	}
	
	return damaged;
}

int AThePackage::CalculateDamage()
{
	//A function that is used to calculate the damage dynamically.

	packageSpeed = distance / timerInt;
	damageAmount = damageAmount + (FMath::TruncToInt(packageSpeed * 0.8f));

	return damageAmount;
}

#pragma region Setters
void AThePackage::SetDestinationCity(FString city)
{
	destinationCity = city;
	UE_LOG(LogTemp, Warning, TEXT("Destination City Set"));
	GEngine->AddOnScreenDebugMessage(-1, 20.0f, FColor::Yellow, TEXT("Destination City Set"));
}

void AThePackage::SetChuteColour(FString colour)
{
	chuteColour = colour;
	UE_LOG(LogTemp, Warning, TEXT("Chute Colour Set"));
}

void AThePackage::SetBoxType(FString type)
{
	boxType = type;
	UE_LOG(LogTemp, Warning, TEXT("Box Type Set"));
}

void AThePackage::SetSimulatePhysics(bool simulate)
{
	packageMeshComponenet->SetSimulatePhysics(simulate);
}

void AThePackage::SetBox(ABoxType1* b) {
	boxType1 = b;
}

void AThePackage::SetBoxType2(ABoxType2 * b)
{
	boxType2 = b;
}

void AThePackage::SetBoxType3(ABoxType3 * b)
{
	boxType3 = b;
}

void AThePackage::SetWhileMoving(bool moving)
{
	whileMoving = moving;
}

void AThePackage::SetPickedUp(bool pick)
{
	pickedUp = pick;
}

void AThePackage::SetHighlightActive(bool active)
{
	highlightActive = active;
}

void AThePackage::SetDropPoint(FVector dPoint)
{
	dropPoint = dPoint;
}

void AThePackage::SetStopPoint(FVector sPoint)
{
	stopPoint = sPoint;
}

void AThePackage::SetDistance(float d)
{
	distance = d;
}

void AThePackage::SetTimerInt(float t)
{
	timerInt = t;
}

#pragma endregion

#pragma region Getters
UStaticMeshComponent * AThePackage::GetPackageMesh()
{
	return packageMeshComponenet;
}
FString AThePackage::GetDestinationCity()
{
	return destinationCity;
}

FString AThePackage::GetChuteColour()
{
	return chuteColour;
}

FString AThePackage::GetBoxType()
{
	return boxType;
}

//The Requirements
FString AThePackage::GetDestinationCityRequirement()
{
	return destinationRequirement;
}
FString AThePackage::GetChuteColourRequirement()
{
	return chuteRequirement;
}
FString AThePackage::GetBoxTypeRequirement()
{
	return boxTypeRequirement;
}

ABoxType1 * AThePackage::GetBoxType1()
{
	return boxType1;
}

ABoxType2 * AThePackage::GetBoxType2() 
{
	return boxType2;
}

ABoxType3 * AThePackage::GetBoxType3()
{
	return boxType3;
}

bool AThePackage::GetHighlightActive() {
	return highlightActive;
}

bool AThePackage::GetPickedUp() {
	return pickedUp;
}

bool AThePackage::GetWhileMoving() {
	return whileMoving;
}

FVector AThePackage::GetDropPoint()
{
	return dropPoint;
}

FVector AThePackage::GetStopPoint()
{
	return stopPoint;
}

float AThePackage::GetDistance()
{
	return distance;
}

float AThePackage::GetTimerInt()
{
	return timerInt;
}
#pragma endregion


