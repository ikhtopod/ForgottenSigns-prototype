// Copyright (c) 2020 Vitaly Lifanov <vitaly@lifanoff.ru>


#include "SaveGameInstance.h"

#include "ForgottenSigns/Public/Gameplay/SaveAndLoad/SSaveGameArchive.h"
#include "ForgottenSigns/Public/Gameplay/SaveAndLoad/SActorSaveData.h"
#include "ForgottenSigns/Public/Gameplay/SaveAndLoad/SaveableActor.h"

#include "GameFramework/WorldSettings.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/BufferArchive.h"
#include "Misc/FileHelper.h"

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

	m_saveGameData.id = "1234";
	m_saveGameData.timestamp = FDateTime::Now();
	m_saveGameData.savedActors = savedActors;

	FBufferArchive binaryData;
	binaryData << m_saveGameData;

	if (binaryData.Num() < 1) return;

	if (FFileHelper::SaveArrayToFile(binaryData, *saveFilename)) {
		UE_LOG(LogTemp, Warning, TEXT("Save Success! %s"), FPlatformProcess::BaseDir());
	} else {
		UE_LOG(LogTemp, Warning, TEXT("Save Failed!"));
	}

	binaryData.FlushCache();
	binaryData.Empty();
}

void USaveGameInstance::LoadGame() {
	TArray<uint8> binaryData;

	if (FFileHelper::LoadFileToArray(binaryData, *saveFilename)) {
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

	fromBinary << m_saveGameData;

	fromBinary.FlushCache();
	binaryData.Empty();
	fromBinary.Close();
}

void USaveGameInstance::RespawnActors() {
	for (FSActorSaveData actorRecord : m_saveGameData.savedActors) {
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

void USaveGameInstance::DestoryExistsSaveableActors() {
	TArray<AActor*> actors;
	FindSaveableActors(actors);

	for (AActor* actor : actors)
		actor->Destroy();
}

void USaveGameInstance::FindSaveableActors(TArray<AActor*>& actors) {
	UGameplayStatics::GetAllActorsWithInterface(GetWorld(), USaveableActor::StaticClass(), actors);
}
