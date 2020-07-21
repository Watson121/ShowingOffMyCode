// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine\World.h"
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "EngineMinimal.h"
#include "Engine.h"
#include "Components\StaticMeshComponent.h"
#include "Components\SceneComponent.h"
#include "GameFramework/Actor.h"
#include "PackageSpawner.generated.h"

class AClock;
class ASwitch;
class UStrikeSystemInstance;
class AThePackage;

UCLASS()
class THANKYOUFORSERVICE_API APackageSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APackageSpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void SettingUpSpawner();
	UFUNCTION(BlueprintCallable)
	void SpawnPackageOnce();
	void SpawnPackage();

	void SetSpawn(bool s);
	bool GetSpawn();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool spawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class AThePackage> objectToSpawn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float spawnTime;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStrikeSystemInstance* gameInstance;

private:

	UStaticMeshComponent* packageSpawnerMeshComponent;
	UStaticMesh* packageSpawnerMesh;
	USceneComponent* spawnLocation;

	UWorld* uWorld;

	float resetTime;

	FVector FSpawnLocation;
	FRotator FSpawnRotation;

};
