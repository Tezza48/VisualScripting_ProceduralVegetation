// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunctionLibrary.h"

void UMyFunctionLibrary::GetMesh(ALandscape * landscape, int sampleLod,  TArray<FVector> & points)
{
	FRawMesh rawMesh;
	landscape->ExportToRawMesh(sampleLod, rawMesh);
	points = rawMesh.VertexPositions;
}
//
////https://docs.unrealengine.com/latest/INT/API/Runtime/Core/Containers/TArray/index.html
//TArray<FVector> & UMyFunctionLibrary::BPQuicksort(TArray<FVector> points)
//{
//	size_t size = points.Num() / sizeof(FVector);
//	QuicksortR(points.GetData(), points.Num() / sizeof(FVector));
//	return points;
//}
//
//void UMyFunctionLibrary::QuicksortR(FVector * buffer, size_t length)
//{
//
//}