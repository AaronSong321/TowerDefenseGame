// Fill out your copyright notice in the Description page of Project Settings.

#include "DebuffBullet.h"
#include <ConstructorHelpers.h>
#include "Enemy.h"

ADebuffBullet::ADebuffBullet()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/TDG/Meshs/Materials/M_Bullet2.M_Bullet2"));
	if (MaterialAsset.Succeeded())
		MeshComp->SetMaterial(0, MaterialAsset.Object);
	Damage = 1.f;

	Debuff = EDebuff::Slow;
	Duration = 3.f;
}

void ADebuffBullet::TransferDamage()
{
	Super::TransferDamage();

	ADebuffTower* DebuffTower = Cast<ADebuffTower>(Tower);
	if (DebuffTower)
		Enemy->SetDebuff(DebuffTower, Duration);
}
