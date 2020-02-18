// Copyright (c) 2020 Vitaly Lifanov <vitaly@lifanoff.ru>


#include "SSaveGameArchive.h"


FSSaveGameArchive::FSSaveGameArchive(FArchive& InInnerArchive) :
	FObjectAndNameAsStringProxyArchive(InInnerArchive, true) {

	ArIsSaveGame = true;
	ArNoDelta = true; // Optional
}
