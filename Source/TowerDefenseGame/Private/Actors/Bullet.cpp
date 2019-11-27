// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include <Components/StaticMeshComponent.h>
#include <ConstructorHelpers.h>
#include <GameFramework/ProjectileMovementComponent.h>
#include "Enemy.h"
#include "Tower.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InitialLifeSpan = 1.f;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComp);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Game/TDG/Meshs/Sphere.Sphere"));
	if (StaticMeshAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(StaticMeshAsset.Object);
		static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/TDG/Meshs/Materials/M_Bullet1.M_Bullet1"));
		if (MaterialAsset.Succeeded())
			MeshComp->SetMaterial(0, MaterialAsset.Object);
	}
	MeshComp->SetRelativeScale3D(FVector(0.2f));
	MeshComp->SetCollisionProfileName("OverlapAll");
	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileComp->InitialSpeed = Speed;
	ProjectileComp->MaxSpeed = Speed;
	ProjectileComp->Velocity = FVector(Speed, 0.f, 0.f);


	FScriptDelegate Del_BeginOverlap;
	Del_BeginOverlap.BindUFunction(this, "HitEnemy");
	MeshComp->OnComponentBeginOverlap.Add(Del_BeginOverlap);

}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::TransferDamage()
{
	Enemy->GetDamage(Tower, Damage);
}

void ABullet::HitEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy && Tower)
	{
		TransferDamage();
		Destroy();
	}
}

