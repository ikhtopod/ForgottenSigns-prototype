// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#include "LibraryFloorRandom.h"
#include "Components/StaticMeshComponent.h"

ALibraryFloorRandom::ALibraryFloorRandom() {
	PrimaryActorTick.bCanEverTick = false;

	libraryFloorComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LibraryFloorComponent"));
	libraryFloorComponent->SetupAttachment(GetRootComponent());
	libraryFloorComponent->SetMobility(EComponentMobility::Stationary);
}

void ALibraryFloorRandom::BeginPlay() {
	Super::BeginPlay();

	currentLibraryFloor = FMath::RandRange(0, FMath::Max<int32>(0, libraryFloors.Num() - 1));
	SetStaticMeshByCurrentIndex();
}

void ALibraryFloorRandom::SetStaticMeshByCurrentIndex() {
	if (!ensure(libraryFloorComponent) || ensure(libraryFloors.Num() == 0)) return;

	libraryFloorComponent->SetStaticMesh(libraryFloors[currentLibraryFloor]);
}
