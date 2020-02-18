// Copyright (c) 2020 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ForgottenSigns/Public/Gameplay/SaveAndLoad/SSaveGameData.h"
#include "SaveGameInstance.generated.h"


/**
 * Class for serialize saving
 */
UCLASS(ClassGroup = "Gameplay|SaveAndLoad")
class FORGOTTENSIGNS_API USaveGameInstance : public UGameInstance {
	GENERATED_BODY()

private:
	// Standard lifetime of drop in seconds
	const float dropLifetime = 900.0f;

	// Z-Order for UI_Loader
	const int32 zOrder = 1000;

public:
	// Save Filename
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveGameInstance|Filename", meta = (Keyword = "save file name filename"))
		FString saveFilename = "fs.sav";

public:
	// Standard lifetime of drop in seconds
	UFUNCTION(BlueprintPure, Category = "SaveGameInstance|Constants", meta = (Keyword = "drop lifetime"))
		FORCEINLINE	float GetDropLifetime() { return dropLifetime; }

	// Standard lifetime of drop in seconds
	UFUNCTION(BlueprintPure, Category = "SaveGameInstance|Constants", meta = (Keyword = "ZOrder Z-Order UI_Loader"))
		FORCEINLINE	int32 GetZOrder() { return zOrder; }

public:
	// Save actors which implemented the ISaveableActor interface
	UFUNCTION(BlueprintCallable, Category = "SaveGameInstance")
		void SaveGame();

	// Load actors which implemented the ISaveableActor interface
	UFUNCTION(BlueprintCallable, Category = "SaveGameInstance")
		void LoadGame();

	// Respawn saved actors
	UFUNCTION(BlueprintCallable, Category = "SaveGameInstance")
		void RespawnActors();

	// Destory exists ISaveableActors objects
	UFUNCTION(BlueprintCallable, Category = "SaveGameInstance")
		void DestoryExistsSaveableActors();

private:
	FSSaveGameData m_saveGameData;

private:
	FORCEINLINE void FindSaveableActors(TArray<AActor*>& actors);
};
