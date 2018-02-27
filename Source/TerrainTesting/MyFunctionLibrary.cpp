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

//https://docs.unrealengine.com/latest/INT/API/Runtime/Core/Containers/TArray/index.html
TArray<FVector> UMyFunctionLibrary::Sort(TArray<FVector> points)
{
	// use TArray::Sort using my predicate to sort the array
	points.Sort(SortPredicate);
	return points;
}

// Function that TArray::Sort can use to compare FVectors
// Return True if A should be before B
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

int UMyFunctionLibrary::Get2DIndex(int x, int y, int width)
{
	return y * width + x;
}

TArray<FVector> UMyFunctionLibrary::GenerateNormals(const TArray<FVector> positions)
{
	// Output array
	TArray<FVector> Normals;
	for (size_t i = 0; i < positions.Num(); i++)
	{
		Normals.Add(FVector(0.f, 0.0f, 1.0f));
	}

	// Width or Height
	size_t size = sqrt(positions.Num());

	// Itterate positions through x and y
	for (size_t y = 1; y < size - 1; y++)
	{
		for (size_t x = 1; x < size - 1; x++)
		{
			
			FVector thisPos = positions[y * size + x];

			FVector up = thisPos - positions[(y + 1) * size + x];
			up.Normalize();
			FVector right = thisPos - positions[y * size + (x + 1)];
			right.Normalize();

			FVector normalA = FVector::CrossProduct(up, right);

			FVector down = thisPos - positions[(y - 1) * size + x];
			down.Normalize();
			FVector left = thisPos - positions[y * size + (x - 1)];
			left.Normalize();

			FVector normalB = FVector::CrossProduct(down, left);

			FVector normalAvg = (normalA + normalB) / 2;
			normalAvg.Normalize();

			Normals[y * size + x] = -normalAvg;
		}
	}

	return Normals;
}
