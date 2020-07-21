// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "Math/UnrealMathUtility.h"
#include "EngineUtils.h"
#include "Vector.h"
#include "Components\StaticMeshComponent.h"
#include "Components\BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxType1.generated.h"

class AThePackage;

UCLASS()
class THANKYOUFORSERVICE_API ABoxType1 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoxType1();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION(BlueprintCallable)
	void DestroyBox();
	UFUNCTION(BlueprintCallable)
	void CreateBox();
#pragma region Setters
	UFUNCTION(BlueprintCallable)
		void SetBoxType(FString type);
	UFUNCTION(BlueprintCallable)
		void SetPickedUp(bool pick);
	UFUNCTION(BlueprintCallable)
		void SetBoxFull(bool full);
	UFUNCTION(BlueprintCallable)
		void SetHighlightActive(bool active);
	UFUNCTION(BlueprintCallable)
		void SetPackageObject(AThePackage* p);
#pragma endregion

#pragma region Getters
	UFUNCTION(BlueprintCallable)
		FString GetBoxType();
	UFUNCTION(BlueprintCallable)
		bool GetPickedUp();
	UFUNCTION(BlueprintCallable)
		bool GetBoxFull();
	UFUNCTION(BlueprintCallable)
		bool GetHighlightActive();
	UFUNCTION(BlueprintCallable)
		AThePackage* GetThePackage();
#pragma endregion

#pragma region Variables
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* boxMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* highlightMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UStaticMeshComponent* boxLidMeshComponent;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UBoxComponent* itemCheck;
#pragma endregion

	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void AttachThePackage();

private:

	UStaticMesh* boxType1; 
	UStaticMesh* boxType1Highlight;
	UStaticMesh* boxType1Lid;

	FString boxType;

	bool pickedUp;
	bool boxFull;
	bool highlightActive;

	UPROPERTY(VisibleAnywhere)
	AThePackage* package;
};
