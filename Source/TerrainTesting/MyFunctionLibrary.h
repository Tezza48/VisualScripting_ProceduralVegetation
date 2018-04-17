// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "string.h"
#include "Engine.h"
#include "Array.h"
#include "Runtime/Landscape/Classes/Landscape.h"
#include "RawMesh.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyFunctionLibrary.generated.h"

// This is a terrible macro but paramaters sidnt work
//#define INDEX_2D(x, y, width) y * size + x

/**
 * 
 */
UCLASS()
class TERRAINTESTING_API UMyFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

private:
	static int Get2DIndex(int x, int y, int width);
public:
	//UFUNCTION(BlueprintPure, DisplayName = "Get Landscape Stuff", Category = "Landscape Helpers")
	//static void GetMesh(ALandscape * landscape, int sampleLod, TArray<FVector> & points);

	UFUNCTION(BlueprintPure, DisplayName = "Get Landscape Stuff", Category = "Landscape Helpers")
	static void GetMesh_Extended(ALandscape * landscape, int sampleLod, TArray<FVector> & points, TArray<FVector> & normals/*, TArray<FVector> & tangents, TArray<FVector> & cotangents*/);
	
	UFUNCTION(BlueprintCallable, DisplayName = "Get Hello", Category = "Landscape Helpers")
	static int GetHello() { return 1; }

	UFUNCTION(BlueprintCallable, DisplayName = "Sort")
	static TArray<FVector> Sort(TArray<FVector> points);
	static bool SortPredicate(const FVector & a, const FVector & b);

	UFUNCTION(BlueprintCallable, DisplayName = "Generate Normals")
	static TArray<FVector> GenerateNormals(const TArray<FVector> positions);

	
};
