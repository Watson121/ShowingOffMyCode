// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxType1.h"
#include "ThePackage.h"

// Sets default values
ABoxType1::ABoxType1()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	boxMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box"));
	highlightMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Highlight"));
	boxLidMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxLid"));
	itemCheck = CreateDefaultSubobject<UBoxComponent>(TEXT("ItemCheck"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> boxType1Object(TEXT("StaticMesh'/Game/Models/BoxType1.BoxType1'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> boxType1HighlightObject(TEXT("StaticMesh'/Game/Models/BoxType1Hightlight.BoxType1Hightlight'"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> boxLidObject(TEXT("StaticMesh'/Game/Models/BoxType1Lid.BoxType1Lid'"));

	boxType1 = boxType1Object.Object;
	boxType1Highlight = boxType1HighlightObject.Object;
	boxType1Lid = boxLidObject.Object;

	if (boxType1) {
		boxMeshComponent->SetStaticMesh(boxType1);
	}

	if (boxType1Highlight) {
		highlightMeshComponent->SetStaticMesh(boxType1Highlight);
	}

	if (boxType1Lid) {
		boxLidMeshComponent->SetStaticMesh(boxType1Lid);
	}

	pickedUp = false;
	boxFull = false;
	highlightActive = false;

	RootComponent = boxMeshComponent;

	FVector location = GetTransform().TransformPosition(boxMeshComponent->GetComponentLocation());

	highlightMeshComponent->SetWorldLocation(FVector(location.X, location.Y, location.Z));
	highlightMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	highlightMeshComponent->SetVisibility(false);

	boxLidMeshComponent->SetWorldLocation(FVector(location.X, location.Y, location.Z + 18.0f));
	boxLidMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	boxLidMeshComponent->SetVisibility(false);

	itemCheck->SetBoxExtent(FVector(13.0f, 13.0f, 5.0f));
	itemCheck->SetWorldLocation(FVector(location.X, location.Y, location.Z + 11.5f));
	itemCheck->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	boxType = "Type 1";

}

// Called when the game starts or when spawned
void ABoxType1::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABoxType1::Tick(float DeltaTime)
{
	
	highlightMeshComponent->SetVisibility(highlightActive);			//This activates if the highlight is active or not, depending if the player hand is near or not.
					
	if (GetPickedUp() == false) {
		this->SetActorEnableCollision(true);
	}
	else if (GetPickedUp() == true) {
		this->SetActorEnableCollision(false);
	}

	if (GetPickedUp() == true) {
		boxMeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
		boxMeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Overlap);
	}
	else if (GetPickedUp() == false) {
		boxMeshComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECollisionResponse::ECR_Block);
		boxMeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	}

	itemCheck->OnComponentEndOverlap.AddDynamic(this, &ABoxType1::OnOverlapEnd);

	Super::Tick(DeltaTime);
}

void ABoxType1::DestroyBox()
{
	Destroy(this);
}

void ABoxType1::CreateBox()
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

void ABoxType1::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
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

void ABoxType1::AttachThePackage()
{
	if (GetBoxFull() == true) {
		GetThePackage()->AttachToComponent(boxMeshComponent, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget, EAttachmentRule::KeepWorld, false));
		GetThePackage()->TurningOffThePhysics();
		GetThePackage()->SetBox(this);
		GetThePackage()->SetBoxType(GetBoxType());

		boxLidMeshComponent->SetVisibility(true);
		boxLidMeshComponent->SetSimulatePhysics(true);
		boxLidMeshComponent->BodyInstance.SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		//itemCheck->BodyInstance.SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}


#pragma region Setters
void ABoxType1::SetBoxType(FString type)
{
	boxType = type;
}
void ABoxType1::SetPickedUp(bool pick)
{
	pickedUp = pick;
}
void ABoxType1::SetBoxFull(bool full)
{
	boxFull = full;
}
void ABoxType1::SetHighlightActive(bool active)
{
	highlightActive = active;
}
void ABoxType1::SetPackageObject(AThePackage * p)
{
	package = p;
}
#pragma endregion

#pragma region Getters
FString ABoxType1::GetBoxType()
{
	return boxType;
}

bool ABoxType1::GetPickedUp()
{
	return pickedUp;
}

bool ABoxType1::GetBoxFull()
{
	return boxFull;
}

bool ABoxType1::GetHighlightActive()
{
	return highlightActive;
}
AThePackage * ABoxType1::GetThePackage()
{
	return package;
}
#pragma endregion


