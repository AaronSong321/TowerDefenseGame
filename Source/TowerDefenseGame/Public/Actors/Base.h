// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TDGameMode.h"
#include "Base.generated.h"

UCLASS()
class TOWERDEFENSEGAME_API ABase : public AActor
{
	GENERATED_BODY()
	
	UPROPERTY(VisibleAnywhere) class USplineComponent* SplineComp;
	UPROPERTY(VisibleAnywhere) class UBillboardComponent* BeginPointComp;
	UPROPERTY(VisibleAnywhere) class UBillboardComponent* EndPointComp;


public:	
	// Sets default values for this actor's properties
	ABase();

	void OnConstruction(const FTransform& Transform) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	float HP;
	UPROPERTY(EditAnywhere, Category = "Settings") float MaxHP = 100.f;
	UPROPERTY(EditAnywhere, Category = "Settings") float SpawnIniteral = 1.f;

	void BeginSpawnEnemy();
	void SpawnEnemy();
	void EndSpawnEnemy();

	ATDGameMode* GameMode;
	FTimerHandle SpawnEnemyHandle;
	void GetDamage(AActor* Attacker, float _Damage);
};
