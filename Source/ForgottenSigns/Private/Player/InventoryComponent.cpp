// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#include "InventoryComponent.h"


UInventoryComponent::UInventoryComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay() {
	Super::BeginPlay();
}

void UInventoryComponent::SetBattery(int32 batteryValue) {
	this->battery = batteryValue > 0 ? batteryValue : 0;
}

int32 UInventoryComponent::GetBattery() const {
	return this->battery;
}

bool UInventoryComponent::HasBattery() const {
	return this->battery > 0;
}

void UInventoryComponent::SetMatches(int32 matchesValue) {
	this->matches = matchesValue > 0 ? matchesValue : 0;
}

int32 UInventoryComponent::GetMatches() const {
	return this->matches;
}

bool UInventoryComponent::HasMatches() const {
	return this->matches > 0;
}
