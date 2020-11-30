// Fill out your copyright notice in the Description page of Project Settings.


#include "MyActor.h"
#include "ProceduralMeshComponent.h"
#include "Components/MeshComponent.h"

// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("mesh"));
	RootComponent = mesh;

	TArray<FVector> vertices;
	vertices.Add(FVector(0, 0, 40));                                // 0th vertice
	vertices.Add(FVector(-17, -23, 0));                           //   1th vertice
	vertices.Add(FVector(17, -23, 0));                           //   2nd vertice
	vertices.Add(FVector(17, 23, 0));                      //    3rd vertice
	vertices.Add(FVector(-17, 23, 0));                           //   4th vertice
	vertices.Add(FVector(0, 0, 0));                      //    5th vertice



	TArray<int32> Triangle;

	//I have created 4 triangle because we need to make sure it is rendered from behind as well. Otherwise, the object will be seen from front only and not from behind.
	Triangle.Add(0);
	Triangle.Add(1);       // for front face - clockwise direction
	Triangle.Add(2);

	Triangle.Add(1);
	Triangle.Add(2);      // for front face - clockwise direction
	Triangle.Add(3);

	Triangle.Add(2);
	Triangle.Add(1);      // for back face - anti-clockwise direction
	Triangle.Add(0);

	Triangle.Add(3);
	Triangle.Add(2);      // for back face - anti-clockwise direction
	Triangle.Add(1);

	TArray<FVector> normals;
	normals.Add(FVector(1, 2, 3));
	normals.Add(FVector(1, 3, 4));
	normals.Add(FVector(1, 4, 5));                    // you need to calculate the direction of normals, using 3d vectors.
	normals.Add(FVector(1, 5, 2));
	normals.Add(FVector(2, 6, 3));
	normals.Add(FVector(3, 6, 4));                    // you need to calculate the direction of normals, using 3d vectors.
	normals.Add(FVector(4, 6, 5));
	normals.Add(FVector(5, 6, 2));

	TArray<FVector2D> UV0;
	UV0.Add(FVector2D(1, 1));
	UV0.Add(FVector2D(0, 1));
	UV0.Add(FVector2D(1, 0));
	UV0.Add(FVector2D(0, 0));

	TArray<FLinearColor> vertexColors;
	vertexColors.Add(FLinearColor(0.75, 0.00, 0.00, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.00, 0.00, 1.0));
	vertexColors.Add(FLinearColor(0.75, 0.00, 0.75, 1.0));                              // the 4th argument determines alpha value (0,1)
	vertexColors.Add(FLinearColor(0.75, 0.00, 0.75, 1.0));

	TArray<FProcMeshTangent> tangents;
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));
	tangents.Add(FProcMeshTangent(0, 1, 0));

	mesh->CreateMeshSection_LinearColor(1, vertices, Triangle, normals, UV0, vertexColors, tangents, false);
}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

