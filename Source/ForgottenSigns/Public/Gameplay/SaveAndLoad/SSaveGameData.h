// Copyright (c) 2020 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

//#include "SActorSaveData.h"
#include "ForgottenSigns/Public/Gameplay/SaveAndLoad/SActorSaveData.h"
#include "SSaveGameData.generated.h"

/**
 * The structure for saving the SActorSaveData structure
 */
USTRUCT(BlueprintType, Category = "Gameplay|SaveAndLoad")
struct FORGOTTENSIGNS_API FSSaveGameData {
	GENERATED_USTRUCT_BODY()

public:
	// Game ID Name
	UPROPERTY(BlueprintReadWrite, Category = "SSaveGameData")
		FName id;

	// timestamp DateTime
	UPROPERTY(BlueprintReadWrite, Category = "SSaveGameData")
		FDateTime timestamp;

	// Saved actors array of SActorSaveData
	UPROPERTY(BlueprintReadWrite, Category = "SSaveGameData")
		TArray<FSActorSaveData> savedActors;

public:
	friend FArchive& operator<<(FArchive& ar, FSSaveGameData& gameData) {
		ar << gameData.id;
		ar << gameData.timestamp;
		ar << gameData.savedActors;

		return ar;
	}
};
