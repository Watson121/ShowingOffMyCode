// Copyright of Adam Tedder 2020

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "XanderAI.generated.h"

UCLASS()
class THANKYOUFORSERVICE_API AXanderAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AXanderAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool part1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool part2;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool part3;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool part4;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool part5;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool part6;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool part7;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool part8;


};
