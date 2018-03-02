// Fill out your copyright notice in the Description page of Project Settings.

#include "TerrainVegetationBase.h"


bool ATerrainVegetationBase::SortPredicate(const FVector a, const FVector b)
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

// Sets default values
ATerrainVegetationBase::ATerrainVegetationBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WaterPlane->SetupAttachment(RootComponent);

	TArray<FVector> vertices;
	vertices.Add(FVector(-0.5f, -0.5f, 0.0f) * TerrainData.size);
	vertices.Add(FVector(-0.5f, 0.5f, 0.0f) * TerrainData.size);
	vertices.Add(FVector(0.5f, 0.5f, 0.0f) * TerrainData.size);
	vertices.Add(FVector(0.5f, -0.5f, 0.0f) * TerrainData.size);

	TArray<int> triangles = TArray<int>{
		0, 1, 2,
		0, 2, 3
	};
	TArray<FVector> normals = TArray<FVector>{
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f },
		{ 0.0f, 0.0f, 1.0f }
	};
	TArray<FVector2D> uv = TArray<FVector2D>{
		{ 0.0f, 0.0f },
		{ 0.0f, 1.0f },
		{ 1.0f, 1.0f },
		{ 1.0f, 0.0f }
	};
	TArray<FColor> color = TArray<FColor>{
		FColor::White,
		FColor::White,
		FColor::White,
		FColor::White
	};
	TArray<FProcMeshTangent> tangents = TArray<FProcMeshTangent>{
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
		{ 0.0f, 1.0f, 0.0f },
	};

	WaterPlane->CreateMeshSection(0, vertices, triangles, normals, uv, color, tangents, false);

}

// Called when the game starts or when spawned
void ATerrainVegetationBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATerrainVegetationBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATerrainVegetationBase::CreateFromLandscape(ALandscape * landscape, int sampleLod)
{
	TerrainData.points.Empty();

	FRawMesh rawMesh;
	// Get the Vertex Data for all of the faces on the Landscape Mesh
	// a higher SampleLOD will return a less detailed (lower vert) list
	landscape->ExportToRawMesh(sampleLod, rawMesh);


	// Get positions
	TArray<FVector> tempPoints = rawMesh.VertexPositions;

	for (size_t i = 0; i < tempPoints.Num(); i++)
	{
		if (!TerrainData.points.Contains(tempPoints[i]))
		{
			TerrainData.points.Add(tempPoints[i]);
		}
	}

	TerrainData.points.Sort(SortPredicate);

	// Get Normals
	TerrainData.normals = GenerateNormals(TerrainData.points);

	TerrainData.size = sqrt(TerrainData.points.Num());
}

TArray<FVector> ATerrainVegetationBase::GenerateNormals(const TArray<FVector> positions)
{// Output array
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