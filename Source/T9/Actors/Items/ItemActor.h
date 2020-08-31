// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemActor.generated.h"


UENUM(BlueprintType)
enum Type
{
	AnyType UMETA(DisplayName = "Any"),
	Tool UMETA(DisplayName = "Tool"),
	Weapon UMETA(DisplayName = "Weapon"),
	Armour UMETA(DisplayName = "Armour"),
	Artefact UMETA(DisplayName = "Artefact"),
	Other UMETA(DisplayName = "Other")
};

UENUM(BlueprintType)
enum SubType
{
	AnySubType UMETA(DisplayName = "Any"),
	PickAxe UMETA(DisplayName = "PickAxe"),
	Axe UMETA(DisplayName = "Axe"),
	Bow UMETA(DisplayName = "Bow"),
	Spear UMETA(DisplayName = "Spear")
};

UENUM(BlueprintType)
enum Socket
{
	NotEquipable UMETA(DisplayName = "NotEquipable"),
	MainHand UMETA(DisplayName = "MainHand"),
	OffHand UMETA(DisplayName = "OffHand"),
	Helmet UMETA(DisplayName = "Helmet"),
	Chest UMETA(DisplayName = "Chest"),
	Legs UMETA(DisplayName = "Legs"),
	Back UMETA(DisplayName = "Back")
};

UENUM(BlueprintType)
enum Rarity
{
	Common UMETA(DisplayName = "Common"),
	UnCommon UMETA(DisplayName = "UnCommon"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary"),
	Mythical UMETA(DisplayName = "Mythical")
};

USTRUCT(BlueprintType)
struct T9_API FItemModifiers {

	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		int ItemDamageBase = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		float ItemDamageMultiplier = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		int ItemHealthBase = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		float ItemHealthMultiplier = 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		int ItemGatherBase = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		float ItemGatherMultiplier = 1;

	inline FItemModifiers& operator+=(const FItemModifiers& Right) {
		this->ItemDamageBase += Right.ItemDamageBase;
		this->ItemDamageMultiplier *= Right.ItemDamageMultiplier;
		this->ItemHealthBase += Right.ItemHealthBase;
		this->ItemHealthMultiplier *= Right.ItemHealthMultiplier;
		this->ItemGatherBase += Right.ItemGatherBase;
		this->ItemGatherMultiplier *= Right.ItemGatherMultiplier;
			return *this;
	}
};

UCLASS()
class T9_API AItemActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FTimerHandle ItemDespawnHandle;

	UFUNCTION(BlueprintCallable)
		void Despawn();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BoxCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ItemMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		int ItemID;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		FString ItemName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<Type> ItemType = AnyType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<SubType> ItemSubType = AnySubType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<Socket> ItemSocket = NotEquipable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		class UTexture2D* ItemImage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		class UPrimitiveComponent* Primitive;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		TEnumAsByte<Rarity> ItemRarity = Rarity::Common;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		class USceneComponent* ItemAnchor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		TMap<TEnumAsByte<Rarity>, class UNiagaraSystem*> Effects;

	UPROPERTY()
		TSubclassOf<UUserWidget> WidgetClass = nullptr;

	UPROPERTY()
		class UItemPickUpWidget* ItemPickUp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		int GoldValue = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item Basics", Meta = (AllowPrivateAccess = "true"))
		struct FItemModifiers Modifiers;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
		class UWidgetComponent* WidgetComponent;


	UFUNCTION(BlueprintCallable)
		int GetItemGoldValue();

	UFUNCTION(BlueprintCallable)
		FString GetItemName();

	UFUNCTION(BlueprintCallable)
		int GetItemID();

	UFUNCTION(BlueprintCallable)
		class UTexture2D* GetItemImage();

	UFUNCTION(BlueprintCallable)
		Type GetItemType();

	UFUNCTION(BlueprintCallable)
		Rarity GetItemRarity();

	UFUNCTION(BlueprintCallable)
		SubType GetItemSubType();

	UFUNCTION(BlueprintCallable)
		Socket GetItemSocket();

	UFUNCTION(BlueprintCallable)
		UStaticMesh* GetItemMesh();

	UFUNCTION()
		FItemModifiers GetItemModifiers();

};
