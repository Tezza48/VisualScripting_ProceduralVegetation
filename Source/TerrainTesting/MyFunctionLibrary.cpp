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
	// Width or Height
	size_t size = sqrt(positions.Num());

	const size_t numDisp = 4;
	FVector displacement[numDisp];

	FVector normalBuffer[numDisp];

	// Itterate positions through x and y
	for (size_t y = 0; y < size; y++)
	{
		for (size_t x = 0; x < size; x++)
		{
			// Do not need to clear the array of displacements as i am overwriting each one

			// Add adjacent positions to array of displacements
			// If the current position is on a boundary,
			// set the unavailable position to 1 unit in that direction

			// Check UP
			// this position needs 1 above it 
			// the ymax is size -1 so i look for size -2
			if (y < size - 2)
			{
				displacement[0] = positions[Get2DIndex(x, y+1, size)];
			}
			else
			{
				displacement[0] = FVector(0.0f, 1.0f, 0.0f);
			}

			// Check Right
			if (x < size - 2)
			{
				displacement[1] = positions[Get2DIndex(x + 1, y, size)];
			}
			else
			{
				displacement[1] = FVector(1.0f, 0.0f, 0.0f);
			}

			// Check Down
			if (y > 0)
			{
				displacement[2] = positions[Get2DIndex(x, y - 1, size)];
			}
			else
			{
				displacement[2] = FVector(0.0f, -1.0f, 0.0f);
			}

			// Check Left
			if (x > 0)
			{
				displacement[3] = positions[Get2DIndex(x - 1, y, size)];
			}
			else
			{
				displacement[3] = FVector(-1.0f, 0.0f, 0.0f);
			}

			// subtract position to get displacement
			// Normalize for good measure
			// Normalizing is possibly not needed
			for (size_t i = 0; i < numDisp; i++)
			{
				if (displacement[i].IsNormalized())
					continue;
				displacement[i] -= positions[Get2DIndex(x, y, size)];
				displacement[i].Normalize();
			}

			// cross product with the next vector in the list
			// working out the normals from the clockwise tangents
			for (size_t i = 1; i < numDisp; i++)
			{
				normalBuffer[i] = FVector::CrossProduct(displacement[i - 1], displacement[i]);
			}
			// cross product of the last with the first
			normalBuffer[0] = FVector::CrossProduct(displacement[numDisp - 1], displacement[0]);

			// Average of vectors is component wise
			// Add Components together
			FVector normalsSum;
			for (size_t i = 0; i < numDisp; i++)
			{
				normalsSum += normalBuffer[i];
			}

			// add sum / numDisp to the normals list
			// Adds the average normal at this point to the list
			Normals.Add(-normalsSum / FVector(numDisp));

		}
	}

	return Normals;
}
