// Fill out your copyright notice in the Description page of Project Settings.

#include "Base.h"
#include <Components/SplineComponent.h>
#include <Components/BillboardComponent.h>
#include <ConstructorHelpers.h>
#include "Enemy.h"

// Sets default values
ABase::ABase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SplineComp = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	SetRootComponent(SplineComp);
	BeginPointComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("BeginPoint"));
	BeginPointComp->SetupAttachment(GetRootComponent());
	static ConstructorHelpers::FObjectFinder<UTexture2D> BeginTextureAsset(TEXT("/Engine/EditorResources/EmptyActor.EmptyActor"));
	if (BeginTextureAsset.Succeeded())
		BeginPointComp->SetSprite(BeginTextureAsset.Object);
	EndPointComp = CreateDefaultSubobject<UBillboardComponent>(TEXT("EndPoint"));
	static ConstructorHelpers::FObjectFinder<UTexture2D> EndTextureAsset(TEXT("/Engine/EditorMaterials/TargetIcon.TargetIcon"));
	if (EndTextureAsset.Succeeded())
		EndPointComp->SetSprite(EndTextureAsset.Object);
}

void ABase::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	EndPointComp->SetWorldLocation(SplineComp->GetWorldLocationAtDistanceAlongSpline(SplineComp->GetSplineLength()));
}

// Called when the game starts or when spawned
void ABase::BeginPlay()
{
	Super::BeginPlay();
	HP = MaxHP;
	GameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode());
	if (GameMode)
		GameMode->Base = this;
}

// Called every frame
void ABase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABase::BeginSpawnEnemy()
{
	GetWorldTimerManager().SetTimer(SpawnEnemyHandle, this, &ABase::SpawnEnemy, SpawnIniteral, true, 0);
}

void ABase::SpawnEnemy()
{
	if (GameMode)
		if (!GameMode->SpawnedAllEnemys())
		{
			FVector SpawnLocation = SplineComp->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World);
			FRotator SpawnRotation = SplineComp->GetTangentAtSplinePoint(0, ESplineCoordinateSpace::World).ToOrientationRotator();
			AEnemy* Enemy = GetWorld()->SpawnActor<AEnemy>(AEnemy::StaticClass(), SpawnLocation, SpawnRotation);
			if (Enemy)
			{
				Enemy->Spline = SplineComp;
				GameMode->SpawnedEnemy();
			}
			else
				GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Spawn enemy failed!"));
			return;
		}
	EndSpawnEnemy();
}

void ABase::EndSpawnEnemy()
{
	if (SpawnEnemyHandle.IsValid())
		GetWorldTimerManager().ClearTimer(SpawnEnemyHandle);
}

void ABase::GetDamage(AActor* Attacker, float _Damage)
{
	HP -= _Damage;
	if (GameMode)
	{
		if (HP <= 0)
			GameMode->BaseBeDestroyed = true;
	}
}

