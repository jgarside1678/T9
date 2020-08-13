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
enum Rarity
{
	Common UMETA(DisplayName = "Common"),
	UnCommon UMETA(DisplayName = "UnCommon"),
	Rare UMETA(DisplayName = "Rare"),
	Epic UMETA(DisplayName = "Epic"),
	Legendary UMETA(DisplayName = "Legendary"),
	Mythical UMETA(DisplayName = "Mythical")
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

};
