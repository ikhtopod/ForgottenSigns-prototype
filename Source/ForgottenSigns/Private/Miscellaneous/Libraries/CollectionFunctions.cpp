// Copyright (c) 2019 Vitaly Lifanov <vitaly@lifanoff.ru>

#include "CollectionFunctions.h"

void UCollectionFunctions::IsEmptyArrayOfClasses(const TArray<UClass*>& classes, bool& isEmpty) {
    isEmpty = UCollectionFunctions::IsEmptyArray<UClass*>(classes);
}

void UCollectionFunctions::IsEmptyArrayOfObjects(const TArray<UObject*>& objects, bool& isEmpty) {
    isEmpty = UCollectionFunctions::IsEmptyArray<UObject*>(objects);
}

void UCollectionFunctions::IsEmptyArrayOfSoftClasses(const TArray<TSoftClassPtr<UObject>>& softClasses, bool& isEmpty) {
    isEmpty = UCollectionFunctions::IsEmptyArray<TSoftClassPtr<UObject>>(softClasses);
}

void UCollectionFunctions::IsEmptyArrayOfSoftObjects(const TArray<TSoftObjectPtr<UObject>>& softObjects,
                                                     bool& isEmpty) {
    isEmpty = UCollectionFunctions::IsEmptyArray<TSoftObjectPtr<UObject>>(softObjects);
}
