// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DebuffComponent.h"
#include "Enemy.generated.h"


UCLASS()
class TOWERDEFENSEGAME_API AEnemy : public AActor
{
	GENERATED_BODY()
	
public:	
	AEnemy();

	UPROPERTY(VisibleAnywhere) class UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere) class USceneComponent* PivotComp;
	UPROPERTY(VisibleAnywhere) class UWidgetComponent* WidgetComp;
	UPROPERTY(VisibleAnywhere) class UDebuffComponent* DebuffComp;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	class USplineComponent* Spline;
	TArray<class ATower*> Towers;
	class ATDGameMode* GameMode;

	float Damage = 5.f;
	float NormalSpeed = 100.f;
	float SlowSpeed = 50.f;
	float TargetSpeed = NormalSpeed;
	float Speed = NormalSpeed;
	float Odometer = 0.f;
	float MaxHP = 30.f;
	float HP;
	
	bool bArrived = false;
	void ArrivedBase();

	void GetDamage(AActor* Attacker, float _Damage);

	void Death();

	class UMaterialInterface* MatR;
	class UMaterialInterface* Mat0;
	class UMaterialInterface* Mat1;

	void BeginSlow();
	void EndSlow();
	void BeginPoison();
	void TickPoison(ADebuffTower* _Tower, float _DeltaTime);
	void EndDebuff();

	void SetDebuff(ADebuffTower* _Tower, float _Duration);
	bool GetDebuffState(EDebuff _Debuff);
	UFUNCTION() void OnActiveDebuff(ADebuffTower* _Tower);
	UFUNCTION() void TickDebuff(ADebuffTower* _Tower, float _DeltaTime);
	UFUNCTION() void OnDeactiveDebuff(ADebuffTower* _Tower);
};
