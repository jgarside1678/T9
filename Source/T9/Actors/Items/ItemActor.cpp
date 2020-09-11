// Fill out your copyright notice in the Description page of Project Settings.

#include "ItemActor.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "NiagaraSystem.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/WidgetComponent.h"
#include "T9/Widgets/ItemPickUpWidget.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"
// Sets default values
AItemActor::AItemActor() 
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* Original = RootComponent;
	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollider->SetCollisionObjectType(ECollisionChannel::ECC_WorldDynamic);
	BoxCollider->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Block);
	BoxCollider->SetHiddenInGame(false);
	BoxCollider->SetCanEverAffectNavigation(false);
	BoxCollider->SetMassOverrideInKg(NAME_None, 10);
	BoxCollider->BodyInstance.bLockXRotation = true;
	BoxCollider->BodyInstance.bLockYRotation = true;
	BoxCollider->BodyInstance.bLockZRotation = true;
	RootComponent = BoxCollider;
	ItemAnchor = CreateDefaultSubobject<USceneComponent>(TEXT("Anchor"));
	ItemAnchor->SetupAttachment(RootComponent);
	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ItemMesh"));
	ItemMesh->SetupAttachment(ItemAnchor);
	ItemMesh->SetCanEverAffectNavigation(false);
	ItemMesh->SetCollisionProfileName("NoCollision");
	//ItemAnchor->SetWorldRotation(FRotator(0));
	//FVector Location = ItemAnchor->GetComponentLocation();
	//ItemAnchor->SetWorldLocation(FVector(Location.X, Location.Y, 10));


	Primitive = (UPrimitiveComponent*)GetComponentByClass(UPrimitiveComponent::StaticClass());
	if (Primitive) {
		Primitive->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		Primitive->SetSimulatePhysics(true);
		Primitive->BodyInstance.bLockYRotation = true;
	}


	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> CommonParticle(TEXT("NiagaraSystem'/Game/Particles/Items/CommonItemEffect.CommonItemEffect'"));
	Effects.Add(Common, CommonParticle.Object);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> UnCommonParticle(TEXT("NiagaraSystem'/Game/Particles/Items/UnCommonItemEffect.UnCommonItemEffect'"));
	Effects.Add(UnCommon, UnCommonParticle.Object);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> RareParticle(TEXT("NiagaraSystem'/Game/Particles/Items/RareItemEffect.RareItemEffect'"));
	Effects.Add(Rare, RareParticle.Object);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> EpicParticle(TEXT("NiagaraSystem'/Game/Particles/Items/EpicItemEffect.EpicItemEffect'"));
	Effects.Add(Epic, EpicParticle.Object);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> LegendaryParticle(TEXT("NiagaraSystem'/Game/Particles/Items/LegendaryItemEffect.LegendaryItemEffect'"));
	Effects.Add(Legendary, LegendaryParticle.Object);
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> MythicalParticle(TEXT("NiagaraSystem'/Game/Particles/Items/MythicalItemEffect.MythicalItemEffect'"));
	Effects.Add(Mythical, MythicalParticle.Object);



	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("Select"));
	static ConstructorHelpers::FClassFinder<UUserWidget> Widget(TEXT("WidgetBlueprint'/Game/UI/ItemPickUp.ItemPickUp_C'"));
	if (Widget.Succeeded()) WidgetClass = Widget.Class;
	if (WidgetComponent) {
		WidgetComponent->SetupAttachment(RootComponent);
		WidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
		WidgetComponent->SetRelativeLocation(FVector(0,0, -500.0f));
		if (WidgetClass != nullptr) {
			WidgetComponent->SetWidgetClass(WidgetClass);
		}
	}


}

// Called when the game starts or when spawned
void AItemActor::BeginPlay()
{
	Super::BeginPlay();
	BoxCollider->SetBoxExtent(FVector(70));
	if (Effects.Contains(ItemRarity)) {
		UNiagaraFunctionLibrary::SpawnSystemAttached(Effects[ItemRarity], BoxCollider, FName(""), FVector(0, 0, -100), FRotator(0), EAttachLocation::SnapToTarget,false);
	}
	if (WidgetComponent) {
		if (WidgetClass != nullptr) {
			WidgetComponent->SetWidgetClass(WidgetClass);
			WidgetComponent->SetVisibility(false);
		}
		ItemPickUp = Cast<UItemPickUpWidget>(WidgetComponent->GetUserWidgetObject());
		if(ItemPickUp)ItemPickUp->ItemMenuInit(this);
	}

	GetWorldTimerManager().SetTimer(ItemDespawnHandle, this, &AItemActor::Despawn, 60, false, 60);
}

// Called every frame
void AItemActor::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
	FVector Start = GetActorLocation();
	FVector End = Start - FVector(0, 0, 160);
	FCollisionQueryParams TraceParams(FName(TEXT("InteractTrace")), true, NULL);
	//TraceParams.bTraceComplex = true;
	TraceParams.AddIgnoredActor(this);
	FHitResult HitDetails = FHitResult(ForceInit);
	bool bIsHit = GetWorld()->LineTraceSingleByChannel( HitDetails, Start, End, ECC_Visibility,	TraceParams	);
	if (bIsHit) {
		float thing = FMath::Lerp(100000, 0, ((HitDetails.Location - Start).Size() / 160));
		Primitive->AddForce(HitDetails.ImpactNormal* thing);
		if(thing > 10000) Primitive->SetLinearDamping(0.4);
		Primitive->SetAngularDamping(0);
	}
	ItemAnchor->AddLocalRotation(FRotator(0, 0.5, 0));
	if (Start.Z < -50) SetActorLocation(FVector(Start.X, Start.Y, 50));
}

void AItemActor::SetSelected()
{
	if (ItemMesh) {
		ItemMesh->SetRenderCustomDepth(true);
	}
	if (WidgetComponent) WidgetComponent->SetVisibility(true);
}

void AItemActor::SetUnSelected()
{
	if (ItemMesh) {
		ItemMesh->SetRenderCustomDepth(false);
	}
	if (WidgetComponent) WidgetComponent->SetVisibility(false);
}

int AItemActor::GetItemGoldValue()
{
	return GoldValue;
}

FString AItemActor::GetItemName()
{
	return ItemName;
}

int AItemActor::GetItemID()
{
	return ItemID;
}

UTexture2D* AItemActor::GetItemImage()
{
	return ItemImage;
}

Type AItemActor::GetItemType()
{
	return ItemType;
}

SubType AItemActor::GetItemSubType()
{
	return ItemSubType;
}

Socket AItemActor::GetItemSocket()
{
	return ItemSocket;
}


void AItemActor::Despawn() {
	if (this) this->Destroy();
}

Rarity AItemActor::GetItemRarity()
{
	return ItemRarity;
}

UStaticMesh* AItemActor::GetItemMesh()
{
	return ItemMesh->GetStaticMesh();
}

FItemModifiers AItemActor::GetItemModifiers()
{
	return Modifiers;
}

FTransform AItemActor::GetItemEquipedTransform()
{
	return ItemEquipedTransform;
}

FTransform AItemActor::GetItemSheathedTransform()
{
	return ItemSheathedTransform;
}
