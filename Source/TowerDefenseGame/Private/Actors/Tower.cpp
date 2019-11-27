// Fill out your copyright notice in the Description page of Project Settings.

#include "Tower.h"
#include <Components/StaticMeshComponent.h>
#include <ConstructorHelpers.h>
#include <Components/SphereComponent.h>
#include <Components/SceneComponent.h>
#include "TDGameMode.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Bullet/RifeBullet.h"
#include "Bullet/CannonBullet.h"
#include "Bullet/DebuffBullet.h"
#include "SlowBullet.h"
#include "PoisonousBullet.h"

ATower::ATower()
{
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComp);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Game/TDG/Meshs/Shape_Cone.Shape_Cone"));
	if (StaticMeshAsset.Succeeded())
		MeshComp->SetStaticMesh(StaticMeshAsset.Object);
	MeshComp->SetCollisionProfileName(TEXT("UI"));
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetupAttachment(GetRootComponent());
	SphereComp->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
	SphereComp->SetSphereRadius(Scope);
	ShootPointComp = CreateDefaultSubobject<USceneComponent>(TEXT("ShootPoint"));
	ShootPointComp->SetupAttachment(GetRootComponent());
	ShootPointComp->SetRelativeLocation(FVector(0.f, 0.f, 100.f));

	FScriptDelegate Del_Clicked;
	Del_Clicked.BindUFunction(this, "OpenUI_Options");
	MeshComp->OnClicked.Add(Del_Clicked);

	FScriptDelegate Del_BeginOverlap;
	Del_BeginOverlap.BindUFunction(this, "EnterScope");
	SphereComp->OnComponentBeginOverlap.Add(Del_BeginOverlap);

	FScriptDelegate Del_EndOverlap;
	Del_EndOverlap.BindUFunction(this, "LeaveScope");
	SphereComp->OnComponentEndOverlap.Add(Del_EndOverlap);
}

void ATower::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode());
	
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	if (GetTarget() && !GameMode->OverState)
	{
		if (!BeginShoot)
		{
			BeginShoot = true;
			GetWorldTimerManager().SetTimer(ShootHandle, this, &ATower::Shoot, GetShootInteral(), true);
		}
	}
	else
	{
		BeginShoot = false;
		GetWorldTimerManager().ClearTimer(ShootHandle);
	}
}

void ATower::OpenUI_Options()
{
	if (GameMode)
		GameMode->OpenUI_Options(Waypoint);
}

void ATower::EnterScope(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		Enemys.Add(Enemy);
		Enemy->Towers.Add(this);
	}
}

void ATower::LeaveScope(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		Enemy->Towers.Remove(this);
		RemoveEnemy(Enemy);
	}
}

void ATower::RemoveEnemy(AEnemy* _Enemy)
{
	TArray<AEnemy*> NewEnemys;
	for (AEnemy* Enemy : Enemys)
		if (Enemy != _Enemy)
			NewEnemys.Add(Enemy);
	Enemys = NewEnemys;
}

bool ATower::GetTarget()
{
	if (Enemys.IsValidIndex(0))
	{
		Target = Enemys[0];
		return true;
	}
	else
	{
		Target = NULL;
		return false;
	}
}

void ATower::Shoot()
{
	FVector SpawnLocation = ShootPointComp->GetComponentLocation();
	FRotator SpawnRotation = FRotationMatrix::MakeFromX(Target->PivotComp->GetComponentLocation() - ShootPointComp->GetComponentLocation()).Rotator();
	UClass* SpawnClass = NULL;
	switch (BulletType)
	{
	case EBullet::Rife:
		SpawnClass = ARifeBullet::StaticClass();
		break;
	case EBullet::Cannon:
		SpawnClass = ACannonBullet::StaticClass();
		break;
	case EBullet::Slow:
		SpawnClass = ASlowBullet::StaticClass();
		break;
	case EBullet::Poison:
		SpawnClass = APoisonousBullet::StaticClass();
		break;
	}
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(SpawnClass, SpawnLocation, SpawnRotation);
	if (Bullet)
		Bullet->Tower = this;
}

float ATower::GetShootInteral()
{
	switch (BulletType)
	{
	case EBullet::Rife:
		return 0.2f;
	case EBullet::Cannon:
		return 1.2f;
	case EBullet::Slow:
		return 1.f;
	case EBullet::Poison:
		return 1.f;
	}
	return 0.2f;
}

