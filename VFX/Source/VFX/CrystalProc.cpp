// Fill out your copyright notice in the Description page of Project Settings.


#include "CrystalProc.h"
#include "Engine.h"

// Sets default values
ACrystalProc::ACrystalProc()
{
    ThisScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    RootComponent = ThisScene;

    ThisMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("GeneratedMesh"));
    ThisMesh->SetupAttachment(RootComponent);

}

void ACrystalProc::PostActorCreated() {
    Super::PostActorCreated();
    GenerateMesh();
}

void ACrystalProc::PostLoad() {
    Super::PostLoad();
    GenerateMesh();
}

void ACrystalProc::GenerateMesh() {     // Each Time GenerateMesh() is called, reset all of the variabes
    Vertices.Reset();			
    Triangles.Reset();
    Normals.Reset();            
    Tangents.Reset();
    UVs.Reset();
    Colours.Reset();

    int32 TriangleIndexCount = 0;
    FVector DefinedShape[8];        // Setting the amount of vertices of a cube to an array
    FProcMeshTangent TangentSetup;

    DefinedShape[0] = FVector(CubeRadius.X, CubeRadius.Y, CubeRadius.Z);        // Forward Top Right
    DefinedShape[1] = FVector(CubeRadius.X, CubeRadius.Y, -CubeRadius.Z);       // Forward Bottom Right
    DefinedShape[2] = FVector(CubeRadius.X, -CubeRadius.Y, CubeRadius.Z);       // Forward Top Left
    DefinedShape[3] = FVector(CubeRadius.X, -CubeRadius.Y, -CubeRadius.Z);      // Forward Bottom Left

    DefinedShape[4] = FVector(-CubeRadius.X, -CubeRadius.Y, CubeRadius.Z);      // Behind Top Right
    DefinedShape[5] = FVector(-CubeRadius.X, -CubeRadius.Y, -CubeRadius.Z);     // Behind Bottom Right
    DefinedShape[6] = FVector(-CubeRadius.X, CubeRadius.Y, CubeRadius.Z);       // Behind Top Left
    DefinedShape[7] = FVector(-CubeRadius.X, CubeRadius.Y, -CubeRadius.Z);      // Behind Bottom Left

    // Setting each of the cubes faces to the respective vertice that is needed to create the faces
    // Front side
    TangentSetup = FProcMeshTangent(0.f, 1.f, 0.f);
    AddQuadMesh(DefinedShape[0], DefinedShape[1], DefinedShape[2], DefinedShape[3], TriangleIndexCount, TangentSetup);

    // Left side
    TangentSetup = FProcMeshTangent(1.f, 0.f, 0.f);
    AddQuadMesh(DefinedShape[2], DefinedShape[3], DefinedShape[4], DefinedShape[5], TriangleIndexCount, TangentSetup);

    // Back side
    TangentSetup = FProcMeshTangent(0.f, -1.f, 0.f);
    AddQuadMesh(DefinedShape[4], DefinedShape[5], DefinedShape[6], DefinedShape[7], TriangleIndexCount, TangentSetup);

    // Right side
    TangentSetup = FProcMeshTangent(-1.f, 0.f, 0.f);
    AddQuadMesh(DefinedShape[6], DefinedShape[7], DefinedShape[0], DefinedShape[1], TriangleIndexCount, TangentSetup);

    // Top side
    TangentSetup = FProcMeshTangent(0.f, 1.f, 0.f);
    AddQuadMesh(DefinedShape[6], DefinedShape[0], DefinedShape[4], DefinedShape[2], TriangleIndexCount, TangentSetup);

    // Bottom side
    TangentSetup = FProcMeshTangent(0.f, -1.f, 0.f);
    AddQuadMesh(DefinedShape[1], DefinedShape[7], DefinedShape[3], DefinedShape[5], TriangleIndexCount, TangentSetup);

    // Setting the mesh to the output from the respective functions
    ThisMesh->CreateMeshSection_LinearColor(0, Vertices, Triangles, Normals, UVs, Colours, Tangents, true);
}

void ACrystalProc::AddTriangleMesh(FVector TopRight, FVector BotRight, FVector BotLeft, int32& TriIndex, FProcMeshTangent Tangent) {
    // Passes in the TriIndex and incrament the index by 1, there are 3 points so this is done 3 times
    int32 Point1 = TriIndex++;
    int32 Point2 = TriIndex++;
    int32 Point3 = TriIndex++;

    // Passes in the vertices for the triangle in the order that is used in AddTriangleMesh()
    Vertices.Add(TopRight);
    Vertices.Add(BotRight);
    Vertices.Add(BotRight);
    Vertices.Add(BotLeft);

    // Adds triangles to each point
    Triangles.Add(Point1);
    Triangles.Add(Point2);
    Triangles.Add(Point3);


    FVector ThisNorm = FVector::CrossProduct(TopRight, BotLeft).GetSafeNormal();    // Takes the difference between the the two vectors to get which way is facing forward
    for (int i = 0; i < 3; i++) {
        Normals.Add(ThisNorm);
        Tangents.Add(Tangent);
        Colours.Add(FLinearColor::Green);
    }
    UVs.Add(FVector2D(1.f, 1.f));  // Top Left
    UVs.Add(FVector2D(0.f, 0.f));  // Bottom Left
    UVs.Add(FVector2D(1.f, 0.f));  // Bottom Right
}

void ACrystalProc::AddQuadMesh(FVector TopRight, FVector BotRight, FVector TopLeft, FVector BotLeft, int32& TriIndex, FProcMeshTangent Tangent) {
    int32 Point1 = TriIndex++;
    int32 Point2 = TriIndex++;
    int32 Point3 = TriIndex++;
    int32 Point4 = TriIndex++;

    Vertices.Add(TopRight);
    Vertices.Add(BotRight);
    Vertices.Add(TopLeft);
    Vertices.Add(BotLeft);

    // Six points are added as an extra triangle is needed for the square mesh (made of 2 triangles)
    Triangles.Add(Point1);
    Triangles.Add(Point2);
    Triangles.Add(Point3);

    Triangles.Add(Point4);
    Triangles.Add(Point3);
    Triangles.Add(Point2);

    FVector ThisNorm = FVector::CrossProduct(TopLeft - BotRight, TopLeft - TopRight).GetSafeNormal();
    for (int i = 0; i < 4; i++) {
        Normals.Add(ThisNorm);
        Tangents.Add(Tangent);
        Colours.Add(FLinearColor::Green);
    }
    UVs.Add(FVector2D(0.f, 1.f));  // Top Left
    UVs.Add(FVector2D(0.f, 0.f));  // Bottom Left
    UVs.Add(FVector2D(1.f, 1.f));  // Top Right
    UVs.Add(FVector2D(1.f, 0.f));  // Bottom Right
}
