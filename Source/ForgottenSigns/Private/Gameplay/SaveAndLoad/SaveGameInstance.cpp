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


const FString USaveGameInstance::m_saveFilename { FPaths::GameSavedDir() + FString("SaveGames/") + "fs.sav" };

void USaveGameInstance::SaveGame() {
	TArray<FSActorSaveData> savedActors;

	TArray<AActor*> actors;
	FindSaveableActors(actors);

	for (AActor* actor : actors) {
		if (actor == nullptr) continue;

		FSActorSaveData actorRecord;
		actorRecord.name = FName(*actor->GetName());
		actorRecord.type = actor->GetClass()->GetPathName();
		actorRecord.transform = actor->GetTransform();

		FMemoryWriter memoryWriter(actorRecord.data, true);
		FSSaveGameArchive ar(memoryWriter);
		actor->Serialize(ar);

		savedActors.Add(actorRecord);
		ISaveableActor::Execute_SaveActorData(actor);
	}//rof

	FSSaveGameData saveGameData;

	saveGameData.id = "1234";
	saveGameData.timestamp = FDateTime::Now();
	saveGameData.savedActors = savedActors;

	FBufferArchive binaryData;
	binaryData << saveGameData;

	if (binaryData.Num() < 1) return;

	if (FFileHelper::SaveArrayToFile(binaryData, *m_saveFilename)) {
		UE_LOG(LogTemp, Warning, TEXT("Save Success! %s"), FPlatformProcess::BaseDir());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Save Failed!"));
	}

	binaryData.FlushCache();
	binaryData.Empty();
}

void USaveGameInstance::LoadGame(FSSaveGameData& saveGameData) {
	TArray<uint8> binaryData;

	if (FFileHelper::LoadFileToArray(binaryData, *m_saveFilename)) {
		UE_LOG(LogTemp, Warning, TEXT("Load Succeeded!"));
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Load Failed!"));
		return;
	}

	if (binaryData.Num() <= 0) {
		UE_LOG(LogTemp, Warning, TEXT("Loaded file empty!"));
		return;
	}

	FMemoryReader fromBinary = FMemoryReader(binaryData, true);
	fromBinary.Seek(0);

	fromBinary << saveGameData;

	fromBinary.FlushCache();
	binaryData.Empty();
	fromBinary.Close();
}

void USaveGameInstance::LoadGame() {
	FSSaveGameData saveGameData;
	LoadGame(saveGameData);
}

void USaveGameInstance::RespawnActors() {
	FSSaveGameData saveGameData;
	LoadGame(saveGameData);

	for (FSActorSaveData actorRecord : saveGameData.savedActors) {
		FVector spawnPos = actorRecord.transform.GetLocation();
		FRotator spawnRot = actorRecord.transform.Rotator();

		FActorSpawnParameters spawnParams;
		spawnParams.Name = actorRecord.name;

		UClass* spawnClass = FindObject<UClass>(ANY_PACKAGE, *actorRecord.type);
		if (spawnClass) {
			AActor* newActor = GWorld->SpawnActor(spawnClass, &spawnPos, &spawnRot, spawnParams);
			FMemoryReader memoryReader(actorRecord.data, true);
			FSSaveGameArchive ar(memoryReader);
			newActor->Serialize(ar);
			newActor->SetActorTransform(actorRecord.transform);
			ISaveableActor::Execute_LoadActorData(newActor);
		}//fi
	}//rof
}

void USaveGameInstance::DeleteSaveFile() {
	if (!FPlatformFileManager::Get().GetPlatformFile().DeleteFile(*m_saveFilename)) {
		UE_LOG(LogTemp, Warning, TEXT("Couldn't delete file \"%s\""), *m_saveFilename);
	}
}

void USaveGameInstance::DestoryExistsSaveableActors() {
	TArray<AActor*> actors;
	FindSaveableActors(actors);

	for (AActor* actor : actors)
		actor->Destroy();
}

void USaveGameInstance::FindSaveableActors(TArray<AActor*>& actors) {
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveableActor::StaticClass(), actors);
}
