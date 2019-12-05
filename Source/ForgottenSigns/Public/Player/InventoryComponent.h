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
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ForgottenSigns", meta = (ClampMin = 0, UIMin = 0))
		int32 battery = 0;

	// Matches count
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "ForgottenSigns", meta = (ClampMin = 0, UIMin = 0))
		int32 matches = 0;

public:
	UInventoryComponent();

protected:
	virtual void BeginPlay() override;

public:
	// Set battery: clamp min 0
	UFUNCTION(BlueprintCallable, Category = "ForgottenSigns")
		void SetBattery(int32 batteryValue);

	// Has Battery
	UFUNCTION(BlueprintCallable, Category = "ForgottenSigns")
		bool HasBattery() const;

	// Set matches: clamp min 0
	UFUNCTION(BlueprintCallable, Category = "ForgottenSigns")
		void SetMatches(int32 matchesValue);

	// Has Matches
	UFUNCTION(BlueprintCallable, Category = "ForgottenSigns")
		bool HasMatches() const;
};
