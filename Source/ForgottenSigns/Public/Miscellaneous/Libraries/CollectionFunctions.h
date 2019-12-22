// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CollectionFunctions.generated.h"

/**
 * Functions for Collections
 */
UCLASS(ClassGroup = "CollectionFunctions")
class FORGOTTENSIGNS_API UCollectionFunctions : public UBlueprintFunctionLibrary {
	GENERATED_BODY()

#pragma region IsEmptyArray
protected:
	/**
		Check whether the array of classes is empty

		@param classes - Array of classes
		@param isEmpty - Result of check
	*/
	UFUNCTION(BlueprintCallable, Category = "CollectionFunctions|Array", meta = (Keywords = "check is empty isempty array class"))
		static void IsEmptyArrayOfClasses(const TArray<UClass*>& classes, bool& isEmpty);

	/**
		Check whether the array of objects is empty

		@param objects - Array of objects
		@param isEmpty - Result of check
	*/
	UFUNCTION(BlueprintCallable, Category = "CollectionFunctions|Array", meta = (Keywords = "check is empty isempty array object"))
		static void IsEmptyArrayOfObjects(const TArray<UObject*>& objects, bool& isEmpty);

	/**
		Check whether the array of soft classes is empty

		@param softClasses - Array of soft classes
		@param isEmpty - Result of check
	*/
	UFUNCTION(BlueprintCallable, Category = "CollectionFunctions|Array", meta = (Keywords = "check is empty isempty array soft class"))
		static void IsEmptyArrayOfSoftClasses(const TArray<TSoftClassPtr<UObject>>& softClasses, bool& isEmpty);

	/**
		Check whether the array of soft objects is empty

		@param softObjects - Array of soft objects
		@param isEmpty - Result of check
	*/
	UFUNCTION(BlueprintCallable, Category = "CollectionFunctions|Array", meta = (Keywords = "check is empty isempty array soft object"))
		static void IsEmptyArrayOfSoftObjects(const TArray<TSoftObjectPtr<UObject>>& softObjects, bool& isEmpty);

private:
	/**
		Check whether Array<T> is empty

		@param list - Array<T>
		@return Result of check
	*/
	template <typename T>
	FORCEINLINE static bool IsEmptyArray(const TArray<T>& list) {
		return list.Num() == 0;
	}
#pragma endregion

};


