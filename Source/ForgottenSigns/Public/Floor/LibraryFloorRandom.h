// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LibraryFloorRandom.generated.h"

class UStaticMeshComponent;

UCLASS(BlueprintType, ClassGroup = "ForgottenSigns")
class FORGOTTENSIGNS_API ALibraryFloorRandom : public AActor {
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadWrite, Category = "ForgottenSigns")
		int32 currentLibraryFloor = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "ForgottenSigns")
		TArray<UStaticMesh*> libraryFloors;

protected:
	UPROPERTY(VisibleDefaultsOnly, Category = "ForgottenSigns")
		UStaticMeshComponent* libraryFloorComponent = nullptr;

public:
	ALibraryFloorRandom();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable, Category = "ForgottenSigns")
		void SetStaticMeshByCurrentIndex();
};
