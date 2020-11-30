// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "CrystalProc.generated.h"


UCLASS()
class VFX_API ACrystalProc : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrystalProc();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh parameters")	// Allows to change the mesh properties on the actor
	FVector CubeRadius = FVector(100.f, 100.f, 100.f);							// Setting the cube's size

protected:
	UPROPERTY(VisibleAnywhere)				 
	USceneComponent* ThisScene;
	UPROPERTY(VisibleAnywhere)
	UProceduralMeshComponent* ThisMesh;		
	 
	virtual void PostActorCreated() override;	// Will trigger when actor is dragged, or created into the game
	virtual void PostLoad() override;			// Will trigger when you open a world
	void GenerateMesh();						// Delcares shapes form

private:
	TArray<FVector>Vertices;			// Defines different points of the mesh, lets program know how to apply static mesh to it
	TArray<int32>Triangles;				// Buffer to point to the vertices, no duplicates of FVectors
	TArray<FVector>Normals;				// Tells engine which way surface is facing
	TArray<FProcMeshTangent>Tangents;	// perpendicular angle to the normal
	TArray<FVector2D>UVs;				// Lets 3D renderer know how to apply the meshes
	TArray<FLinearColor>Colours;		// Applys colour to vertice

	void AddTriangleMesh(FVector TopRight, FVector BotRight, FVector BotLeft, int32& TriIndex, FProcMeshTangent Tangent);					// Passes in the Trianges vertices, tangent and an index
	void AddQuadMesh(FVector TopRight, FVector BotRight, FVector TopLeft, FVector BotLeft, int32& TriIndex, FProcMeshTangent Tangent);		// Passes in an additional vertice for the square

};
