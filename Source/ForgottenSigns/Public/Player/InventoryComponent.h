// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


// Inventory Component
UCLASS(ClassGroup = (ForgottenSigns), meta = (BlueprintSpawnableComponent))
class FORGOTTENSIGNS_API UInventoryComponent : public UActorComponent {
	GENERATED_BODY()

public:
	// Battery count
	UPROPERTY(EditDefaultsOnly, Category = "ForgottenSigns", meta = (ClampMin = 0, UIMin = 0))
		int32 battery = 0;

	// Matches count
	UPROPERTY(EditDefaultsOnly, Category = "ForgottenSigns", meta = (ClampMin = 0, UIMin = 0))
		int32 matches = 0;

public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:

#pragma region Battery Functions
	// Set battery: clamp min 0
	UFUNCTION(BlueprintCallable, Category = "ForgottenSigns")
		void SetBattery(int32 batteryValue);

	// Get battery value
	UFUNCTION(BlueprintPure, Category = "ForgottenSigns")
		int32 GetBattery() const;

	// Has Battery
	UFUNCTION(BlueprintPure, Category = "ForgottenSigns")
		bool HasBattery() const;

#pragma endregion

#pragma region Matches Functions

	// Set matches: clamp min 0
	UFUNCTION(BlueprintCallable, Category = "ForgottenSigns")
		void SetMatches(int32 matchesValue);

	// Get matches value
	UFUNCTION(BlueprintPure, Category = "ForgottenSigns")
		int32 GetMatches() const;

	// Has Matches
	UFUNCTION(BlueprintPure, Category = "ForgottenSigns")
		bool HasMatches() const;

#pragma endregion

};
