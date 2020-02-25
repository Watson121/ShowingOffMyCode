// Fill out your copyright notice in the Description page of Project Settings.

#include "BoxType3.h"
#include "ThePackage.h"

// Sets default values
ABoxType3::ABoxType3()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	highlightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Highlight"));
	boxLidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxLid"));
	itemCheck = CreateDefaultSubobject<UCapsuleComponent>(TEXT("ItemCheck"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> boxType3Object(TEXT("StaticMesh'/Game/Models/BoxType3.BoxType3'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> boxType3HighlightObject(TEXT("StaticMesh'/Game/Models/BoxType3Highlight.BoxType3Highlight'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> boxLidObject(TEXT("StaticMesh'/Game/Models/BoxType3Lid.BoxType3Lid'"));

	boxType3 = boxType3Object.Object;
	boxType3Highlight = boxType3HighlightObject.Object;
	boxType3Lid = boxLidObject.Object;

	if (boxType3) {
		boxMeshComponent->SetStaticMesh(boxType3);
	}

	if (boxType3Highlight) {
		highlightMeshComponent->SetStaticMesh(boxType3Highlight);
	}

	if (boxType3Lid) {
		boxLidMeshComponent->SetStaticMesh(boxType3Lid);
	}

	pickedUp = false;
	boxFull = false;
	highlightActive = false;

	RootComponent = boxMeshComponent;

	FVector location = GetTransform().TransformPosition(boxMeshComponent->GetComponentLocation());

	boxMeshComponent->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));

	highlightMeshComponent->SetWorldLocation(FVector(location.X, location.Y, location.Z));
	highlightMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	highlightMeshComponent->SetVisibility(false);

	boxLidMeshComponent->SetWorldLocation(FVector(location.X, location.Y, location.Z + 18.0f));
	boxLidMeshComponent->SetWorldRotation(FRotator(0.0f, 90.0f, 0.0f));
	boxLidMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	boxLidMeshComponent->SetVisibility(false);
	
	itemCheck->SetCapsuleHalfHeight(10.0f);
	itemCheck->SetCapsuleRadius(20.0f);
	itemCheck->SetWorldScale3D(FVector(0.4f, 0.4f, 0.4f));
	itemCheck->SetWorldLocation(FVector(location.X, location.Y, location.Z + 10.25f));
	itemCheck->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	boxType = "Type 3";
}

// Called when the game starts or when spawned
void ABoxType3::BeginPlay()
{
	CreateBox();
	Super::BeginPlay();
}

// Called every frame
void ABoxType3::Tick(float DeltaTime)
{
	highlightMeshComponent->SetVisibility(highlightActive);			//This activates if the highlight is active or not, depending if the player hand is near or not.

	switch (pickedUp) {
	case true:
		/*So if the player has picked up this box, it means that it should be overlaping with the rest of the world, and not have any collision enable
		If collision has not be enable because I do want it to be able to interact with other objects in the environemnt while in this state*/

		boxMeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
		boxMeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
		this->SetActorEnableCollision(false);
		break;
	case false:
		/*So if the played has not picked up the box/dropped the box. The box should be able to interact with the world and make collsions with it.*/

		boxMeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Block);
		boxMeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Block);
		this->SetActorEnableCollision(true);
		break;
	}

	itemCheck->OnComponentEndOverlap.AddDynamic(this, &ABoxType3::OnOverlapEnd);

	Super::Tick(DeltaTime);

}

void ABoxType3::DestroyBox()
{
	Destroy(this);
}

void ABoxType3::CreateBox()
{
#pragma region Box Mesh and Box Lid Mesh
	//Setting the physics controls
	boxMeshComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	boxMeshComponent->BodyInstance.SetObjectType(ECollisionChannel::ECC_GameTraceChannel3);
	boxLidMeshComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);

	//Preset Channels
	boxMeshComponent->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Block);
	boxMeshComponent->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Block);
	boxMeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Block);
	boxMeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	boxMeshComponent->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Block);
	boxMeshComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Block);
	boxMeshComponent->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Block);
	boxMeshComponent->SetCollisionResponseToChannel(ECC_Destructible, ECollisionResponse::ECR_Block);

	//Custom Channels
	boxMeshComponent->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECollisionResponse::ECR_Overlap);
	boxMeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
	boxMeshComponent->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);

	boxMeshComponent->SetSimulatePhysics(true);
	boxLidMeshComponent->SetSimulatePhysics(false);
#pragma endregion

#pragma region Collider Box
	//Setting the physics controls
	itemCheck->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	itemCheck->BodyInstance.SetObjectType(ECollisionChannel::ECC_WorldDynamic);

	//Preset Channels
	itemCheck->SetCollisionResponseToChannel(ECC_Visibility, ECollisionResponse::ECR_Overlap);
	itemCheck->SetCollisionResponseToChannel(ECC_Camera, ECollisionResponse::ECR_Overlap);
	itemCheck->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	itemCheck->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	itemCheck->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	itemCheck->SetCollisionResponseToChannel(ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	itemCheck->SetCollisionResponseToChannel(ECC_Vehicle, ECollisionResponse::ECR_Overlap);
	itemCheck->SetCollisionResponseToChannel(ECC_Destructible, ECollisionResponse::ECR_Overlap);

	//Custom Channels
	itemCheck->SetCollisionResponseToChannel(ECC_EngineTraceChannel1, ECollisionResponse::ECR_Overlap);
	itemCheck->SetCollisionResponseToChannel(ECC_GameTraceChannel2, ECollisionResponse::ECR_Overlap);
	itemCheck->SetCollisionResponseToChannel(ECC_GameTraceChannel3, ECollisionResponse::ECR_Overlap);

	itemCheck->SetGenerateOverlapEvents(true);
#pragma endregion
}


void ABoxType3::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		SetPackageObject(Cast<AThePackage>(OtherActor));

		if (GetThePackage()) {
			SetBoxFull(true);
			AttachThePackage();
		}
	}
}

void ABoxType3::AttachThePackage()
{
	if (GetBoxFull() == true) {
		GetThePackage()->AttachToComponent(boxMeshComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false));
		GetThePackage()->TurningOffThePhysics();
		GetThePackage()->SetBoxType3(this);
		GetThePackage()->SetBoxType(GetBoxType());

		boxLidMeshComponent->SetVisibility(true);
		boxLidMeshComponent->SetSimulatePhysics(true);
		boxLidMeshComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//itemCheck->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


#pragma region Setters
void ABoxType3::SetBoxType(FString type)
{
	boxType = type;
}
void ABoxType3::SetPickedUp(bool pick)
{
	pickedUp = pick;
}
void ABoxType3::SetBoxFull(bool full)
{
	boxFull = full;
}
void ABoxType3::SetHighlightActive(bool active)
{
	highlightActive = active;
}
void ABoxType3::SetPackageObject(AThePackage * p)
{
	package = p;
}
#pragma endregion

#pragma region Getters
FString ABoxType3::GetBoxType()
{
	return boxType;
}

bool ABoxType3::GetPickedUp()
{
	return pickedUp;
}

bool ABoxType3::GetBoxFull()
{
	return boxFull;
}

bool ABoxType3::GetHighlightActive()
{
	return highlightActive;
}
AThePackage * ABoxType3::GetThePackage()
{
	return package;
}
#pragma endregion

