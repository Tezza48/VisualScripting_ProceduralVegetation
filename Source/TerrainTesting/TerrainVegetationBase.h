// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Landscape.h"
#include "ProceduralMeshComponent.h"
#include "RawMesh.h"
#include "GameFramework/Actor.h"
#include "TerrainVegetationBase.generated.h"

USTRUCT(BlueprintType)
struct FTerrainMeshData
{
	GENERATED_BODY()

public:
	UPROPERTY()
	int size;

	UPROPERTY()
	TArray<FVector> points;

	UPROPERTY()
	TArray<FVector> normals;

	//UPROPERTY()
	//TArray<FVector> Tangents;

	UPROPERTY()
	TArray<int> indices;

	void Empty()
	{
		size = 100;
		points.Empty();
		normals.Empty();
		indices.Empty();
	}

};

UCLASS()
class TERRAINTESTING_API ATerrainVegetationBase : public AActor
{
	GENERATED_BODY()

private:
	static bool SortPredicate(const FVector a, const FVector b);

protected:

	UPROPERTY()
	UProceduralMeshComponent * WaterPlane = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("WaterPlane"));

	UPROPERTY()
	FTerrainMeshData TerrainData;

public:
	UPROPERTY()
	float WaterHeight = 0.0f;

public:	
	// Sets default values for this actor's properties
	ATerrainVegetationBase();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, DisplayName = "Get Landscape Stuff", Category = "Landscape Helpers")
	void CreateFromLandscape(ALandscape * landscape, int sampleLod);

	UFUNCTION(BlueprintCallable, DisplayName = "Generate Normals")
	TArray<FVector> GenerateNormals(const TArray<FVector> positions);
	
	
};
