// Fill out your copyright notice in the Description page of Project Settings.


#include "Chute.h"

// Sets default values
AChute::AChute()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AChute::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

