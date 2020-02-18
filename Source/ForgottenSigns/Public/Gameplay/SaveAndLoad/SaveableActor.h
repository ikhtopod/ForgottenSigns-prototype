// Copyright (c) 2020 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SaveableActor.generated.h"


UINTERFACE(BlueprintType, Category = "Gameplay|SaveAndLoad")
class USaveableActor : public UInterface {
	GENERATED_BODY()
};

/**
 * Interface for serializable actors
 */
class FORGOTTENSIGNS_API ISaveableActor {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ISaveableActor")
		void SaveActorData();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "ISaveableActor")
		void LoadActorData();
};
