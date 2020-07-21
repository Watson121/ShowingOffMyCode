// Fill out your copyright notice in the Description page of Project Settings.


#include "PackageSpawner.h"
#include "ThePackage.h"
#include "StrikeSystemInstance.h"
#include "Clock.h"

// Sets default values
APackageSpawner::APackageSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	packageSpawnerMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Package_Spawner"));
	spawnLocation = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn_Location"));

	RootComponent = packageSpawnerMeshComponent;
	spawnLocation->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

#pragma region Setting up the mesh component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> packageSpawner(TEXT("StaticMesh'/Game/Models/PackageDrop.PackageDrop'"));

	packageSpawnerMesh = packageSpawner.Object;

	if (packageSpawnerMesh)
		packageSpawnerMeshComponent->SetStaticMesh(packageSpawnerMesh);
#pragma endregion
	spawn = false;
}

// Called when the game starts or when spawned
void APackageSpawner::BeginPlay()
{	
	Super::BeginPlay();
}

// Called every frame
void APackageSpawner::Tick(float DeltaTime)
{
	if (spawn) {
		spawnTime -= GetWorld()->GetDeltaSeconds();
	}

	if (spawn && spawnTime <= 0) {
		SpawnPackage();
		spawnTime = resetTime;
	}

	Super::Tick(DeltaTime);

}

void APackageSpawner::SettingUpSpawner()
{
	gameInstance = Cast<UStrikeSystemInstance>(GetGameInstance());
	uWorld = GetWorld();

	if (gameInstance) {
		switch (gameInstance->currentGameMode)
		{
		case GAMEMODE_Tutorial:

			/*When the game is in the tutorial, the spawn package will not
			spawn unless told to by the game*/

			spawnTime = 10.0f;
			spawn = false;
			break;
		case GAMEMODE_TimeTrial:

			/*If Time Trial is choosen, depenidng on the difficulty. The spawn time for
			the player will be different*/

			switch (gameInstance->difficultLevel) {
			case DIFFICULTY_easy:
				spawnTime = 10.0f;
				break;
			case DIFFICULTY_medium:
				spawnTime = 8.0f;
				break;
			case DIFFICULTY_hard:
				spawnTime = 5.0f;
				break;
			}
			spawn = true;
			break;
		case GAMEMODE_Story:

			/*When the player chooses story mode, this will set the spawn time for
			story mode.*/

			spawnTime = 10.0f;
			spawn = true;
			break;
		}
	}

	resetTime = spawnTime;
}

void APackageSpawner::SpawnPackageOnce()
{
	FActorSpawnParameters spawnParas;
	spawnParas.Owner = this;
	spawnParas.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FSpawnLocation = spawnLocation->GetComponentLocation();
	FRotator fRotator = FRotator::ZeroRotator;

	uWorld->SpawnActor<AThePackage>(objectToSpawn, FSpawnLocation, fRotator, spawnParas);
}

void APackageSpawner::SpawnPackage()
{

	FActorSpawnParameters spawnParas;
	spawnParas.Owner = this;
	spawnParas.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FSpawnLocation = spawnLocation->GetComponentLocation();
	FRotator fRotator = FRotator::ZeroRotator;

	uWorld->SpawnActor<AThePackage>(objectToSpawn, FSpawnLocation, fRotator, spawnParas);
}

void APackageSpawner::SetSpawn(bool s)
{
	spawn = s;
}

bool APackageSpawner::GetSpawn()
{
	return spawn;
}


