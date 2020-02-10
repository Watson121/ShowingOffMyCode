// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void OnCompHit(UPrimitiveComponent* MyComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, bool SelfMoved, 
		FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit);

#pragma region Setters
	UFUNCTION(BlueprintCallable)
		void RequirementCheck();

	UFUNCTION(BlueprintCallable)
		void SetDestinationCity(FString city);
	UFUNCTION(BlueprintCallable)
		void SetChuteColour(FString colour);
	UFUNCTION(BlueprintCallable)
		void SetBoxType(FString type);
	UFUNCTION(BlueprintCallable)
		void SetBoxSize(FString size);

	UFUNCTION(BlueprintCallable)
		void SetSimulatePhysics(bool simulate);

	UFUNCTION(BlueprintCallable)
		void SetBox(ABoxTypeAndSize* b);

	UFUNCTION(BlueprintCallable)
		void SetWhileMoving(bool moving);
	UFUNCTION(BlueprintCallable)
		void SetPickedUp(bool pick);
	UFUNCTION(BlueprintCallable)
		void SetHighlightActive(bool active);

	UFUNCTION(BlueprintCallable)
		void SetDropPoint(FVector dPoint);
	UFUNCTION(BlueprintCallable)
		void SetStopPoint(FVector sPoint);
	
	UFUNCTION(BlueprintCallable)
		void SetDistance(float d);
	UFUNCTION(BlueprintCallable)
		void SetTimerInt(float t);

#pragma endregion

#pragma region Getters

	UFUNCTION(BlueprintCallable)
		UStaticMeshComponent* GetPackageMesh();

	//Getting Input Variables
	UFUNCTION(BlueprintCallable)
		FString GetDestinationCity();
	UFUNCTION(BlueprintCallable)
		FString GetChuteColour();
	UFUNCTION(BlueprintCallable)
		FString GetBoxType();
	UFUNCTION(BlueprintCallable)
		FString GetBoxSize();

	//Getting Requirements Variables
	UFUNCTION(BlueprintCallable)
		FString GetDestinationCityRequirement();
	UFUNCTION(BlueprintCallable)
		FString GetChuteColourRequirement();
	UFUNCTION(BlueprintCallable)
		FString GetBoxTypeRequirement();
	UFUNCTION(BlueprintCallable)
		FString GetBoxSizeRequirement();

	//Getting Booleans
	UFUNCTION(BlueprintCallable)
		bool GetHighlightActive();
	UFUNCTION(BlueprintCallable)
		bool GetPickedUp();
	UFUNCTION(BlueprintCallable)
		bool GetWhileMoving();

	//Getting FVectors
	UFUNCTION(BlueprintCallable)
		FVector GetDropPoint();
	UFUNCTION(BlueprintCallable)
		FVector GetStopPoint();

	//Getting Ints and Floats
	UFUNCTION(BlueprintCallable)
		float GetDistance();
	UFUNCTION(BlueprintCallable)
		float GetTimerInt();

	UFUNCTION(BlueprintCallable)
		ABoxTypeAndSize* GetBox();
#pragma endregion

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* packageMeshComponenet;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* highlightMeshComponenet;

private:

#pragma region Declerations

#pragma region The Requirements
		FString destinationRequirement;
		FString chuteRequirement;
		FString boxTypeRequirement;
		FString boxSizeRequirement;
#pragma endregion

#pragma region Input Variables
		FString destinationCity;
		FString chuteColour;
		FString boxType;
		FString boxSize;
		bool pacakgedCorrectly;
#pragma endregion

#pragma region Damage
		bool damaged;
		float packageSpeed;
		int damageAmount;
#pragma endregion
		
#pragma region Other Components
		ARequirementsBoard* requirementsBoard;
		ABoxTypeAndSize* box;
		AStrikeSystem* strikeSystem;
		AFinalReportSystem* finalReportSystem;
		AQuotaBoard* quotaBoard;
#pragma endregion

#pragma region Arrays
		TArray<FString> destinationCities;
		TArray<FString> chuteColours;
		TArray<FString> boxTypes;
		TArray<FString> boxSizes;
		TArray<FString> objectNames;
#pragma endregion

#pragma region Static Meshes
		FString objectName;
		UStaticMesh* packageMesh;
		UStaticMesh* vaseMesh;
		UStaticMesh* consoleMesh;
		UStaticMesh* toyMesh;
		UStaticMesh* placeholderMesh;
		UStaticMesh* vaseHighlighMesh;
		UStaticMesh* consoleHighlightMesh;
		UStaticMesh* toyHighlightMesh;
#pragma endregion
		
		//Calculating Damage
		FVector dropPoint;
		FVector stopPoint;
		float distance;
		float timerInt;

		bool whileMoving;
		bool pickedUp;
		bool highlightActive;
		int numberOfRequirementsCorrect;

#pragma endregion

#pragma region Functions
		void SetRequirements();
		void SetPackageMesh();
		UFUNCTION(BlueprintCallable)
		void CallRequirementsBoard();
		void DestroyThis();

		bool DamageCheck();
		int CalculateDamage();
#pragma endregion



};
