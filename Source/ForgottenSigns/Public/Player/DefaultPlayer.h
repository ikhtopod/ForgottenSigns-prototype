// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultPlayer.generated.h"


class UInventoryComponent;
class UIndicatorsComponent;
class UCharacterMovementComponent;
class UCameraComponent;


// Default Player
UCLASS(BlueprintType, ClassGroup = "ForgottenSigns")
class FORGOTTENSIGNS_API ADefaultPlayer : public ACharacter {
	GENERATED_BODY()

private:
	static constexpr float RUNNIG_FACTOR = 2.0f;

private:
	// length of inteact line
	float interactLength = 180.0f;
	float walkSpeed = 0.0f;
	UCharacterMovementComponent* characterMovementComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = "ForgottenSigns")
		UCameraComponent* cameraComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = "ForgottenSigns")
		UInventoryComponent* inventoryComponent = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = "ForgottenSigns")
		UIndicatorsComponent* indicatorsComponent = nullptr;

protected:
	// Mouse Sensitivity
	UPROPERTY(BlueprintReadWrite, Category = "ForgottenSigns|Mouse", meta = (ClampMin = 0.0f, UIMin = 0.0f))
		float mouseSensitivity = 30.0f;

public:
	ADefaultPlayer();

private:
	// To determine if an actor implements an interface in both C++ and Blueprints
	static bool IsInteractableActor(AActor* actor);

private:
	void MoveForward(float scaleValue);
	void MoveRight(float scaleValue);
	void Turn(float scaleValue);
	void LookUp(float scaleValue);

	void StartJump();
	void StopJump();
	void StartRun();
	void StopRun();
	void StartCrouch();
	void StopCrouch();

	void Using();

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;
};
