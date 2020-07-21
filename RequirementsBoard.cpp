// Fill out your copyright notice in the Description page of Project Settings.


#include "RequirementsBoard.h"
#include "ThePackage.h"

// Sets default values
ARequirementsBoard::ARequirementsBoard()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	requirementsScreen = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Requirements Screen"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> placeholderMeshObject(TEXT("StaticMesh'/Game/Models/RequirementBoard.RequirementBoard'"));

	requirementsScreenObj = placeholderMeshObject.Object;

	if (requirementsScreenObj) {
		requirementsScreen->SetStaticMesh(requirementsScreenObj);
	}

	RootComponent = requirementsScreen;

	destinationCity = "PLEASE PICK PACKAGE UP";
	chuteColour = "PLEASE PICK PACKAGE UP";
	typeOfBox = "PLEASE PICK PACKAGE UP";
}

// Called when the game starts or when spawned
void ARequirementsBoard::BeginPlay()
{
	for (TActorIterator<AThePackage> ActorItr(GetWorld()); ActorItr; ++ActorItr) {
		package = *ActorItr;
	}

	Super::BeginPlay();
	
}

// Called every frame
void ARequirementsBoard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARequirementsBoard::SetDestinationCity(FString city)
{
	destinationCity = city;
}

void ARequirementsBoard::SetChuteColour(FString colour)
{
	chuteColour = colour;
}

void ARequirementsBoard::SetBoxType(FString type)
{
	typeOfBox = type;
}


