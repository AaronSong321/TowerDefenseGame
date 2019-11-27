// Fill out your copyright notice in the Description page of Project Settings.

#include "PoisonousBullet.h"
#include <ConstructorHelpers.h>

APoisonousBullet::APoisonousBullet()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/TDG/Meshs/Materials/M_Bullet4.M_Bullet4"));
	if (MaterialAsset.Succeeded())
		MeshComp->SetMaterial(0, MaterialAsset.Object);
	Debuff = EDebuff::Poison;
	
}
