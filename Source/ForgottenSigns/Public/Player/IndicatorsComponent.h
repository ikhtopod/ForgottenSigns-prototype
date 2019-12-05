// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IndicatorsComponent.generated.h"


UCLASS(ClassGroup = (ForgottenSigns), meta = (BlueprintSpawnableComponent))
class FORGOTTENSIGNS_API UIndicatorsComponent : public UActorComponent {
	GENERATED_BODY()

public:
	// Health indicator
	UPROPERTY(EditDefaultsOnly, Category = "ForgottenSigns",
		meta = (ClampMin = 0.0f, ClampMax = 100.0f, UIMin = 0.0f, UIMax = 100.0f))
		float health = 100.0f;

	// Mind indicator
	UPROPERTY(EditDefaultsOnly, Category = "ForgottenSigns",
		meta = (ClampMin = 0.0f, ClampMax = 100.0f, UIMin = 0.0f, UIMax = 100.0f))
		float mind = 100.0f;

public:
	UIndicatorsComponent();

protected:
	virtual void BeginPlay() override;

public:

#pragma region Health Functions
	// Set Health: clamp 0.0f-100.0f
	UFUNCTION(BlueprintCallable, Category = "ForgottenSigns")
		void SetHealth(float healthValue);

	// Get Health value
	UFUNCTION(BlueprintPure, Category = "ForgottenSigns")
		float GetHealth() const;

	// Has Health
	UFUNCTION(BlueprintPure, Category = "ForgottenSigns")
		bool HasHealth() const;

#pragma endregion

#pragma region Mind Functions

	// Set Mind: clamp 0.0f-100.0f
	UFUNCTION(BlueprintCallable, Category = "ForgottenSigns")
		void SetMind(float mindValue);

	// Get Mind value
	UFUNCTION(BlueprintPure, Category = "ForgottenSigns")
		float GetMind() const;

	// Has Mind
	UFUNCTION(BlueprintPure, Category = "ForgottenSigns")
		bool HasMind() const;

#pragma endregion

};
