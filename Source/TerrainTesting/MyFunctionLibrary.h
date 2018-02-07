// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Array.h"
#include "Landscape.h"
#include "string.h"
#include "Developer/RawMesh/Public/RawMesh.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TERRAINTESTING_API UMyFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
public:
	UFUNCTION(BlueprintPure, DisplayName = "Get Landscape Stuff", Category = "Landscape Helpers")
	static void GetMesh(ALandscape * landscape, int sampleLod, TArray<FVector> & points);
	
	UFUNCTION(BlueprintCallable, DisplayName = "Get Hello", Category = "Landscape Helpers")
	static int GetHello() { return 1; }

	UFUNCTION(BlueprintCallable, DisplayName = "Sort")
	static TArray<FVector> Sort(TArray<FVector> points);
	static bool SortPredicate(const FVector & a, const FVector & b);
};
