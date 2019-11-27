// Fill out your copyright notice in the Description page of Project Settings.

#include "DebuffTower.h"
#include <ConstructorHelpers.h>
#include <Materials/MaterialInterface.h>
#include "DataType.h"
#include "Enemy.h"

ADebuffTower::ADebuffTower()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/TDG/Meshs/Shape_TriPyramid.Shape_TriPyramid"));
	if (MeshAsset.Succeeded())
		MeshComp->SetStaticMesh(MeshAsset.Object);
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatAsset(TEXT("/Game/TDG/Meshs/Materials/M_Tower3.M_Tower3"));
	if (MatAsset.Succeeded())
		MeshComp->SetMaterial(0, MatAsset.Object);
	BulletType = EBullet::Slow;
	Debuff = EDebuff::Slow;
}

bool ADebuffTower::GetTarget()
{
	for (AEnemy* I_Enemy : Enemys)
	{
		if (!I_Enemy->GetDebuffState(Debuff))
		{
			Target = I_Enemy;
			return true;
		}
	}
	if (Enemys.IsValidIndex(0))
	{
		Target = Enemys[0];
		return true;
	}
	Target = nullptr;
	return false;
}
