// Fill out your copyright notice in the Description page of Project Settings.

#include "Waypoint.h"
#include <Components/StaticMeshComponent.h>
#include <ConstructorHelpers.h>
#include "TDGameMode.h"
#include "Tower/RifeTower.h"
#include "Tower/CannonTower.h"
#include "Tower/DebuffTower.h"
#include "SlowTower.h"
#include "PoisonousTower.h"

AWaypoint::AWaypoint()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComp);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Game/TDG/Meshs/Shape_Cube.Shape_Cube"));
	if (StaticMeshAsset.Succeeded())
		MeshComp->SetStaticMesh(StaticMeshAsset.Object);
	MeshComp->SetRelativeScale3D(FVector(1.f, 1.f, 0.2f));
	MeshComp->SetCollisionProfileName(TEXT("UI"));
	SpawnPointComp = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint"));
	SpawnPointComp->SetupAttachment(GetRootComponent());
	SpawnPointComp->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
	
	FScriptDelegate Del;
	Del.BindUFunction(this, "OpenUI_Options");
	MeshComp->OnClicked.Add(Del);

}

void AWaypoint::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode());
}

void AWaypoint::OpenUI_Options()
{
	if (GameMode)
		GameMode->OpenUI_Options(this);
}

void AWaypoint::SpawnTower(ETower::Type TowerType)
{
	bHasTower = true;
	FVector SpawnLocation = SpawnPointComp->GetComponentLocation();
	FRotator SpawnRotation = FRotator::ZeroRotator;
	UClass* SpawnClass = nullptr;
	switch (TowerType)
	{
	case ETower::Rife:
		SpawnClass = ARifeTower::StaticClass();
		break;
	case ETower::Cannon:
		SpawnClass = ACannonTower::StaticClass();
		break;
	case ETower::Slow:
		SpawnClass = ASlowTower::StaticClass();
		break;
	case ETower::Poison:
		SpawnClass = APoisonousTower::StaticClass();
		break;
	}
	Tower = GetWorld()->SpawnActor<ATower>(SpawnClass, SpawnLocation, SpawnRotation);
	if (Tower)
		Tower->Waypoint = this;
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Spawn tower failed!"));
}

void AWaypoint::DestroyTower()
{
	if (Tower)
	{
		Tower->Destroy();
		Tower = nullptr;
	}
	bHasTower = false;
}

