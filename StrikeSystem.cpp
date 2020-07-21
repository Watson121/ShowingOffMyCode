// Fill out your copyright notice in the Description page of Project Settings.


#include "StrikeSystem.h"
#include "StrikeSystemInstance.h"

// Sets default values
AStrikeSystem::AStrikeSystem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	clockBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Clock"));
	strikeOne = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StrikeOne"));
	strikeTwo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StrikeTwo"));
	strikeThree = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StrikeThree"));

	/*Below are constructor helpers that find the objects in the game*/

	static ConstructorHelpers::FObjectFinder<UStaticMesh> clockObject(TEXT("StaticMesh'/Game/Models/Clock.Clock'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> strikeObject(TEXT("StaticMesh'/Game/Models/StrikeSymbol.StrikeSymbol'"));
	static ConstructorHelpers::FObjectFinder<USoundCue> sound(TEXT("SoundCue'/Game/SoundQues/S_Strike.S_Strike'"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> material(TEXT("'/Game/StarterBundle/ModularScifiProps/Materials/MI_Light_Red.MI_Light_Red'"));

	clockModel = clockObject.Object;
	strikeModel = strikeObject.Object;
	strikeSound = sound.Object;
	mLightRed = material.Object;

	if (clockModel) {
		clockBase->SetStaticMesh(clockModel);
	}

	if (strikeModel) {
		strikeOne->SetStaticMesh(strikeModel);
		strikeTwo->SetStaticMesh(strikeModel);
		strikeThree->SetStaticMesh(strikeModel);
	}

	RootComponent = clockBase;

	FVector location = GetTransform().TransformPosition(clockBase->GetComponentLocation());

	strikeOne->SetWorldLocation(FVector(location.X, location.Y - 17.0f, location.Z));
	strikeOne->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	strikeTwo->SetWorldLocation(FVector(location.X, location.Y, location.Z));
	strikeTwo->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	strikeThree->SetWorldLocation(FVector(location.X, location.Y + 17.0f, location.Z));
	strikeThree->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AStrikeSystem::BeginPlay()
{
	gameInstance = Cast<UStrikeSystemInstance>(GetGameInstance());
	Super::BeginPlay();
}

// Called every frame
void AStrikeSystem::Tick(float DeltaTime)
{
	if (gameInstance) {
		gameInstance->numberOfStrikes = numberOfStrikes;
	}

	Super::Tick(DeltaTime);

}

int AStrikeSystem::GetNumberOfStrikes()
{
	return numberOfStrikes;
}

void AStrikeSystem::SetNumberOfStrikes()
{
	numberOfStrikes++;	//Adds one to number of strikes
	/*Below is a switch statement that turns on the mLightRed material, which means that this strike has been reached*/

	switch (numberOfStrikes)
	{
	case 1:
		strikeOne->SetMaterial(0, mLightRed);
		break;
	case 2:
		strikeTwo->SetMaterial(0, mLightRed);
		break;
	case 3:
		strikeThree->SetMaterial(0, mLightRed);
		break;
	}

	PlayStrikeSound();
}

void AStrikeSystem::PlayStrikeSound()
{
	/*This function plays the strike sound que at the location of the clock base*/
	UGameplayStatics::PlaySoundAtLocation(clockBase, strikeSound, GetTransform().TransformPosition(clockBase->GetComponentLocation()), 1.0f, 1.0f, 0.0f, nullptr, nullptr);
}

