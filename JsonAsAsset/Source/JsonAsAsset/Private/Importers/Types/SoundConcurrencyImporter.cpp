﻿// Copyright JAA Contributors 2024-2025

#include "Importers/Types/SoundConcurrencyImporter.h"

#include "Sound/SoundConcurrency.h"

bool USoundConcurrencyImporter::ImportData() {
	try {
		TSharedPtr<FJsonObject> Properties = JsonObject->GetObjectField("Properties");
		USoundConcurrency* SoundConcurrency = NewObject<USoundConcurrency>(Package, USoundConcurrency::StaticClass(), *FileName, RF_Public | RF_Standalone);
		GetObjectSerializer()->DeserializeObjectProperties(Properties, SoundConcurrency);

		// Handle edit changes, and add it to the content browser
		SavePackage();
		HandleAssetCreation(SoundConcurrency);
	} catch (const char* Exception) {
		UE_LOG(LogJson, Error, TEXT("%s"), *FString(Exception));
		return false;
	}

	return true;
}