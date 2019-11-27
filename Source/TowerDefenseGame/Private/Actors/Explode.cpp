// Fill out your copyright notice in the Description page of Project Settings.

#include "Explode.h"
#include <Components/SphereComponent.h>
#include <Particles/ParticleSystemComponent.h>
#include <ConstructorHelpers.h>
#include <Kismet/GameplayStatics.h>
#include <Kismet/KismetSystemLibrary.h>
#include "Enemy.h"
#include "Tower.h"

AExplode::AExplode()
{
	InitialLifeSpan = 0.2f;
	RootComp = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(RootComp);
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetupAttachment(GetRootComponent());
	SphereComp->SetCollisionProfileName(TEXT("OverlapAll"));

	FScriptDelegate Del_BeginOverlap;
	Del_BeginOverlap.BindUFunction(this, "BeginOverlap");
	SphereComp->OnComponentBeginOverlap.Add(Del_BeginOverlap);
}

void AExplode::OnConstruction(const FTransform& Transform)
{
	SphereComp->SetSphereRadius(Range);
}

void AExplode::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		float Length = (GetActorLocation() - Enemy->GetActorLocation()).Size();
		float RealDamage = FMath::GetMappedRangeValueClamped(FVector2D(0.f, Range), FVector2D(Damage, 2.f), Length);
		if (Tower)
			Enemy->GetDamage(Tower, RealDamage);
		else
			GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Tower is invalid!"));
	}
}

void AExplode::BeginPlay()
{
	Super::BeginPlay();
	
	UParticleSystem* ParticleSystem = LoadObject<UParticleSystem>(nullptr, TEXT("/Game/TDG/Particles/P_Explosion.P_Explosion"));
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ParticleSystem, FTransform(FRotator(0.f), GetActorLocation(), FVector(1.f)), true, EPSCPoolMethod::None);
}



