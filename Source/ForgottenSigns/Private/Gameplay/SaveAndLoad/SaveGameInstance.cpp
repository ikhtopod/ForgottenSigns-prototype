// Copyright (c) 2020 Vitaly Lifanov <vitaly@lifanoff.ru>


#include "SaveGameInstance.h"

#include "ForgottenSigns/Public/Gameplay/SaveAndLoad/SSaveGameArchive.h"
#include "ForgottenSigns/Public/Gameplay/SaveAndLoad/SActorSaveData.h"
#include "ForgottenSigns/Public/Gameplay/SaveAndLoad/SaveableActor.h"

#include "GameFramework/WorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/BufferArchive.h"
#include "HAL/PlatformFilemanager.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"


const FString USaveGameInstance::m_saveFilename { "fs.sav" };

FString USaveGameInstance::GetAbsolutePathSaveFilename() { return FPaths::ProjectSavedDir() + FString("SaveGames/") + m_saveFilename; }

FName USaveGameInstance::GetCurrentLevelName() { return GetWorld()->GetCurrentLevel()->GetFName(); }


void USaveGameInstance::FindSaveableActors(TArray<AActor*>& actors) {
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveableActor::StaticClass(), actors);
}


void USaveGameInstance::SaveBinaryData() {
	TArray<FSActorSaveData> savedActors;

	TArray<AActor*> actors;
	FindSaveableActors(actors);

	for (AActor* actor : actors) {
		if (actor == nullptr) continue;

		ISaveableActor::Execute_SaveActorData(actor);

		FSActorSaveData actorRecord;
		actorRecord.name = FName(*actor->GetName());
		actorRecord.type = actor->GetClass()->GetPathName();
		actorRecord.transform = actor->GetTransform();

		FMemoryWriter memoryWriter { actorRecord.data, true };
		FSSaveGameArchive ar { memoryWriter };
		actor->Serialize(ar);

		savedActors.Add(actorRecord);
	}//rof

	FSSaveGameData saveGameData;

	saveGameData.id = "1234";
	saveGameData.timestamp = FDateTime::Now();
	saveGameData.savedActors = savedActors;

	FBufferArchive binaryData;
	binaryData << saveGameData;

	if (binaryData.Num() < 1) return;

	if (FFileHelper::SaveArrayToFile(binaryData, *GetAbsolutePathSaveFilename())) {
		UE_LOG(LogTemp, Warning, TEXT("Save Success! %s"), *GetAbsolutePathSaveFilename());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Save Failed!"));
	}//fi

	binaryData.FlushCache();
	binaryData.Empty();
}


void USaveGameInstance::LoadBinaryData() {
	TArray<uint8> binaryData;

	if (!HasBinarySaveFile()) {
		UE_LOG(LogTemp, Warning, TEXT("File \"%s\" not exists!"), *GetAbsolutePathSaveFilename());
		return;
	}

	if (FFileHelper::LoadFileToArray(binaryData, *GetAbsolutePathSaveFilename())) {
		UE_LOG(LogTemp, Warning, TEXT("Load Succeeded!"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Load Failed!"));
		return;
	}

	if (binaryData.Num() <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("Loaded file empty!"));
		return;
	}

	FMemoryReader fromBinary { binaryData, true };
	fromBinary.Seek(0);

	FSSaveGameData saveGameData;
	fromBinary << saveGameData;

	fromBinary.FlushCache();
	binaryData.Empty();
	fromBinary.Close();

	RespawnLoadedActors(saveGameData);
}


void USaveGameInstance::DeleteBinarySaveFile() {
	if (!HasBinarySaveFile()) {
		UE_LOG(LogTemp, Warning, TEXT("File \"%s\" not exists!"), *GetAbsolutePathSaveFilename());
	}

	if (!FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*GetAbsolutePathSaveFilename())) {
		UE_LOG(LogTemp, Warning, TEXT("Couldn't delete file \"%s\""), *GetAbsolutePathSaveFilename());
	}
}


bool USaveGameInstance::HasBinarySaveFile() {
	return FPlatformFileManager::Get().GetPlatformFile().FileExists(*GetAbsolutePathSaveFilename());
}


void USaveGameInstance::DestroyExistsSaveableActors() {
	TArray<AActor*> actors;
	FindSaveableActors(actors);

	for (AActor* actor : actors)
		actor->Destroy();
}


void USaveGameInstance::RespawnLoadedActors(FSSaveGameData& saveGameData) {
	for (FSActorSaveData actorRecord : saveGameData.savedActors) {
		FVector spawnPos = actorRecord.transform.GetLocation();
		FRotator spawnRot = actorRecord.transform.Rotator();

		FActorSpawnParameters spawnParams;
		spawnParams.Name = actorRecord.name;

		UClass* spawnClass = FindObject<UClass>(ANY_PACKAGE, *actorRecord.type);
		if (spawnClass && spawnClass->ImplementsInterface(USaveableActor::StaticClass())) {
			AActor* newActor = GWorld->SpawnActor(spawnClass, &spawnPos, &spawnRot, spawnParams);

			if (newActor) {
				FMemoryReader memoryReader(actorRecord.data, true);
				FSSaveGameArchive ar(memoryReader);
				newActor->Serialize(ar);
				newActor->SetActorTransform(actorRecord.transform);

				ISaveableActor::Execute_LoadActorData(newActor);
			}//fi
		}//fi
	}//rof
}
