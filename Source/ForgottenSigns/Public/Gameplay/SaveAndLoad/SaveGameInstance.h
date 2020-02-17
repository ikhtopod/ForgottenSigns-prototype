// Copyright (c) 2020 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "SaveGameInstance.generated.h"

/**
 * Class for serialize saving
 */
UCLASS(ClassGroup = "Gameplay|SaveAndLoad")
class FORGOTTENSIGNS_API USaveGameInstance : public UGameInstance {
	GENERATED_BODY()

public:
	// Standard lifetime of drop in seconds
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveGameInstance|Constants", meta = (Keyword = "drop lifetime"))
		float dropLifetime = 900.0f;

	// Z-Order for UI_Loader
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SaveGameInstance|Loader", meta = (Keyword = "ZOrder Z-Order UI_Loader"))
		int32 zOrder = 1000;
};
