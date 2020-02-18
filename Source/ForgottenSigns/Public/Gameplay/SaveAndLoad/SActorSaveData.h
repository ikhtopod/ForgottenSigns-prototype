// Copyright (c) 2020 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "SActorSaveData.generated.h"

/**
 * the SActorSaveData structure
 */
USTRUCT(BlueprintType, Category = "Gameplay|SaveAndLoad")
struct FORGOTTENSIGNS_API FSActorSaveData {
	GENERATED_USTRUCT_BODY()

public:
	// Actor Class string
	UPROPERTY(BlueprintReadWrite, Category = "SActorSaveData")
		FString type;

	// Actor Name
	UPROPERTY(BlueprintReadWrite, Category = "SActorSaveData")
		FName name;

	// Actor Transform
	UPROPERTY(BlueprintReadWrite, Category = "SActorSaveData")
		FTransform transform;

	// Actor Data array of uint8
	UPROPERTY(BlueprintReadWrite, Category = "SActorSaveData")
		TArray<uint8> data;

public:
	friend FArchive& operator<<(FArchive& ar, FSActorSaveData& actorData) {
		ar << actorData.type;
		ar << actorData.name;
		ar << actorData.transform;
		ar << actorData.data;

		return ar;
	}
};
