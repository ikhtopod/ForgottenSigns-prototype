// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#include "InventoryComponent.h"


UInventoryComponent::UInventoryComponent() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UInventoryComponent::BeginPlay() {
	Super::BeginPlay();
}

void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
