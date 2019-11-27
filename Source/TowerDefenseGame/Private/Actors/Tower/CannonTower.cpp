// Fill out your copyright notice in the Description page of Project Settings.

#include "CannonTower.h"
#include <ConstructorHelpers.h>
#include <Materials/MaterialInterface.h>

ACannonTower::ACannonTower()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/TDG/Meshs/Shape_QuadPyramid.Shape_QuadPyramid"));
	if (MeshAsset.Succeeded())
		MeshComp->SetStaticMesh(MeshAsset.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatAsset(TEXT("/Game/TDG/Meshs/Materials/M_Tower2.M_Tower2"));
	if (MatAsset.Succeeded())
		MeshComp->SetMaterial(0, MatAsset.Object);
	BulletType = EBullet::Cannon;
}
