// Fill out your copyright notice in the Description page of Project Settings.

#include "RifeTower.h"
#include <ConstructorHelpers.h>
#include <Materials/MaterialInterface.h>
#include "Tower.h"

ARifeTower::ARifeTower()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatAsset(TEXT("/Game/TDG/Meshs/Materials/M_Tower1.M_Tower1"));
	if (MatAsset.Succeeded())
		MeshComp->SetMaterial(0, MatAsset.Object);
	BulletType = EBullet::Rife;
}
