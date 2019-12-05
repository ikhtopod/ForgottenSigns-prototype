// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#include "IndicatorsComponent.h"


UIndicatorsComponent::UIndicatorsComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UIndicatorsComponent::BeginPlay() {
	Super::BeginPlay();
}

void UIndicatorsComponent::SetHealth(float healthValue) {
	this->health = FMath::Clamp<float>(healthValue, 0.0f, 100.0f);
}

float UIndicatorsComponent::GetHealth() const {
	return this->health;
}

bool UIndicatorsComponent::HasHealth() const {
	return this->health > 0.0f;
}

void UIndicatorsComponent::SetMind(float mindValue) {
	this->mind = FMath::Clamp<float>(mindValue, 0.0f, 100.0f);
}

float UIndicatorsComponent::GetMind() const {
	return this->mind;
}

bool UIndicatorsComponent::HasMind() const {
	return this->mind > 0.0f;
}
