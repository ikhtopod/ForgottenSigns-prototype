// Copyright (c) 2020 Vitaly Lifanov <vitaly@lifanoff.ru>

#pragma once

#include "CoreMinimal.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
// #include "SSaveGameArchive.generated.h"


struct FORGOTTENSIGNS_API FSSaveGameArchive : public FObjectAndNameAsStringProxyArchive {
	/**
	 * Create new instance.
	 *
	 * @param InInnerArchive - archive to proxy
	 */
	FSSaveGameArchive(FArchive& InInnerArchive);
};
