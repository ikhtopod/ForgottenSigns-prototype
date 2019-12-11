// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#include "DefaultPlayer.h"

#include "ForgottenSigns/Public/Player/InventoryComponent.h"
#include "ForgottenSigns/Public/Player/IndicatorsComponent.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/WorldSettings.h"


ADefaultPlayer::ADefaultPlayer() {
	inventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory"));
	indicatorsComponent = CreateDefaultSubobject<UIndicatorsComponent>(TEXT("Indicators"));

	cameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	cameraComponent->SetupAttachment(GetCapsuleComponent());
	cameraComponent->RelativeLocation = FVector { -10.0f, 0.0f, 60.0f };
	cameraComponent->bUsePawnControlRotation = true;
	cameraComponent->PostProcessSettings.AutoExposureMethod = EAutoExposureMethod::AEM_Histogram;
	cameraComponent->PostProcessSettings.AutoExposureBias = -2.0f;
	cameraComponent->PostProcessSettings.AutoExposureMinBrightness = 0.005f;
	cameraComponent->PostProcessSettings.AutoExposureMaxBrightness = 1.0f;
	cameraComponent->PostProcessSettings.AutoExposureSpeedUp = 4.0f;
	cameraComponent->PostProcessSettings.AutoExposureSpeedDown = 4.0f;

	characterMovementComponent = GetCharacterMovement();

	FNavAgentProperties& navAgentProperties = characterMovementComponent->GetNavAgentPropertiesRef();
	navAgentProperties.bCanWalk = true;
	navAgentProperties.bCanJump = true;
	navAgentProperties.bCanCrouch = true;

	walkSpeed = characterMovementComponent->MaxWalkSpeed;

	PrimaryActorTick.bCanEverTick = true;
}

void ADefaultPlayer::BeginPlay() {
	Super::BeginPlay();
}

void ADefaultPlayer::SetupPlayerInputComponent(UInputComponent* inputComponent) {
	Super::SetupPlayerInputComponent(inputComponent);

	inputComponent->BindAxis(TEXT("MoveForward"), this, &ADefaultPlayer::MoveForward);
	inputComponent->BindAxis(TEXT("MoveRight"), this, &ADefaultPlayer::MoveRight);

	inputComponent->BindAxis(TEXT("Turn"), this, &ADefaultPlayer::Turn);
	inputComponent->BindAxis(TEXT("LookUp"), this, &ADefaultPlayer::LookUp);

	inputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ADefaultPlayer::StartJump);
	inputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Released, this, &ADefaultPlayer::StopJump);

	inputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Pressed, this, &ADefaultPlayer::StartRun);
	inputComponent->BindAction(TEXT("Run"), EInputEvent::IE_Released, this, &ADefaultPlayer::StopRun);

	inputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Pressed, this, &ADefaultPlayer::StartCrouch);
	inputComponent->BindAction(TEXT("Crouch"), EInputEvent::IE_Released, this, &ADefaultPlayer::StopCrouch);
}

void ADefaultPlayer::MoveForward(float scaleValue) {
	AddMovementInput(GetActorForwardVector(), scaleValue);
}

void ADefaultPlayer::MoveRight(float scaleValue) {
	AddMovementInput(GetActorRightVector(), scaleValue);
}

void ADefaultPlayer::Turn(float scaleValue) {
	AddControllerYawInput(scaleValue * mouseSensitivity * GetWorld()->DeltaTimeSeconds);
}

void ADefaultPlayer::LookUp(float scaleValue) {
	AddControllerPitchInput(scaleValue * mouseSensitivity * GetWorld()->DeltaTimeSeconds);
}

void ADefaultPlayer::StartJump() {
	this->Jump();
}

void ADefaultPlayer::StopJump() {
	this->StopJumping();
}

void ADefaultPlayer::StartRun() {
	characterMovementComponent->MaxWalkSpeed *= RUNNIG_FACTOR;
}

void ADefaultPlayer::StopRun() {
	characterMovementComponent->MaxWalkSpeed = walkSpeed;
}

void ADefaultPlayer::StartCrouch() {
	this->Crouch();
}

void ADefaultPlayer::StopCrouch() {
	this->UnCrouch();
}
