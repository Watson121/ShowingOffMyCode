// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PackageSealer.generated.h"

UCLASS()
class THANKYOUFORSERVICE_API APackageSealer : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APackageSealer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool toolOn;


};
