// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DataType/DataType.h"
#include "Tower.generated.h"

UCLASS()
class TOWERDEFENSEGAME_API ATower : public AActor
{
	GENERATED_BODY()
	
public:	
	ATower();

	UPROPERTY(VisibleAnywhere) class UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere) class USphereComponent* SphereComp;
	UPROPERTY(VisibleAnywhere) class USceneComponent* ShootPointComp;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

public:
	class ATDGameMode* GameMode;
	class AWaypoint* Waypoint;
	TArray<class AEnemy*> Enemys;
	class AEnemy* Target;

	float Scope = 300;
	UFUNCTION() void OpenUI_Options();
	UFUNCTION() void EnterScope(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION() void LeaveScope(class UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void RemoveEnemy(AEnemy* _Enemy);
	virtual bool GetTarget();
	void Shoot();
	bool BeginShoot = false;
	float GetShootInteral();

	FTimerHandle ShootHandle;
	EBullet::Type BulletType;
};
