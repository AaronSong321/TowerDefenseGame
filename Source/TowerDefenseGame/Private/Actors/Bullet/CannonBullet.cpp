// Fill out your copyright notice in the Description page of Project Settings.

#include "CannonBullet.h"
#include <ConstructorHelpers.h>
#include "Explode.h"
#include <Kismet/GameplayStatics.h>

ACannonBullet::ACannonBullet()
{

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/TDG/Meshs/Materials/M_Bullet3.M_Bullet3"));
	if (MaterialAsset.Succeeded())
		MeshComp->SetMaterial(0, MaterialAsset.Object);
	MeshComp->SetRelativeScale3D(FVector(0.3f));
	Damage = 12.f;
}

void ACannonBullet::TransferDamage()
{
	FVector SpawnLocation = GetActorLocation();
	FRotator SpawnRotation = GetActorRotation();
	UClass* SpawnClass = AExplode::StaticClass();
	AExplode* Explode = GetWorld()->SpawnActorDeferred<AExplode>(SpawnClass, FTransform(SpawnRotation, SpawnLocation, FVector(1.f)));
	// AExplode* Explode = GetWorld()->SpawnActor<AExplode>(SpawnClass, SpawnLocation, SpawnRotation);
	if (Explode)
	{
		Explode->Damage = Damage;
		Explode->Range = Range;
		Explode->Tower = Tower;
		UGameplayStatics::FinishSpawningActor(Explode, FTransform(SpawnRotation, SpawnLocation, FVector(1.f)));
	}
}