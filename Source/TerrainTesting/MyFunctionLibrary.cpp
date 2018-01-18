// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunctionLibrary.h"

void UMyFunctionLibrary::GetMesh(ALandscape * landscape, int sampleLod,  TArray<FVector> & points)
{
	FRawMesh rawMesh;
	landscape->ExportToRawMesh(sampleLod, rawMesh);
	points = rawMesh.VertexPositions;
}
