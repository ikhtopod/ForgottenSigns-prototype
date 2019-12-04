// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DefaultPlayer.generated.h"


class UCharacterMovementComponent;
class UCameraComponent;

UCLASS(BlueprintType, ClassGroup = "ForgottenSigns|Player")
class FORGOTTENSIGNS_API ADefaultPlayer : public ACharacter {
	GENERATED_BODY()

private:
	static constexpr float RUNNIG_FACOR = 2.0f;

private:
	float walkSpeed = 0.0f;
	UCharacterMovementComponent* characterMovementComponent = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "ForgottenSigns")
		UCameraComponent* cameraComponent = nullptr;

public:
	// Mouse Sensitivity
	UPROPERTY(Category = "ForgottenSigns|Mouse", EditAnywhere, BlueprintReadWrite, meta = (ClampMin = 0.0f, UIMin = 0.0f))
		float mouseSensitivity = 30.0f;

public:
	ADefaultPlayer();

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

protected:
	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComponent) override;
};
