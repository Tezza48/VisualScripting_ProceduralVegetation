// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFunctionLibrary.h"

void UMyFunctionLibrary::GetMesh(ALandscape * landscape, int sampleLod,  TArray<FVector> & points)
{
	FRawMesh rawMesh;
	// Get the Vertex Data for all of the faces on the Landscape Mesh
	// a higher SampleLOD will return a less detailed (lower vert) list
	landscape->ExportToRawMesh(sampleLod, rawMesh);
	// return the points using the Array referance
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

//TArray<FVector> & UMyFunctionLibrary::BPQuicksort(TArray<FVector> points)
//{
//	QuicksortR(points.GetData(), points.Num() / sizeof(FVector));
//}

TArray<FVector> UMyFunctionLibrary::Sort(TArray<FVector> points)
{
	// use TArray::Sort using my predicate to sort the array
	points.Sort(SortPredicate);
	return points;
}

// Function that TArray::Sort can use to compare FVectors
bool UMyFunctionLibrary::SortPredicate(const FVector & a, const FVector & b)
{
	if (a.Y < b.Y)
	{
		// if a's y is less we know it has to be before b
		return true;
	}
	else if (a.Y == b.Y && a.X < b.X)
	{
		// if they're at equal y, if a's x is less than b's x, true
		return true;
	}
	else
	{
		// else b is before a
		return false;
	}
}