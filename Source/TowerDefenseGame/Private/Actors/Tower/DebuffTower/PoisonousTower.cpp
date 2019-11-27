// Fill out your copyright notice in the Description page of Project Settings.

#include "PoisonousTower.h"
#include <ConstructorHelpers.h>

APoisonousTower::APoisonousTower()
{
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MatAsset(TEXT("/Game/TDG/Meshs/Materials/M_Tower4.M_Tower4"));
	if (MatAsset.Succeeded())
		MeshComp->SetMaterial(0, MatAsset.Object);
	Debuff = EDebuff::Poison;
}
