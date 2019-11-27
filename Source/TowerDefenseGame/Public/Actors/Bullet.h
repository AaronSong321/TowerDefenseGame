// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class TOWERDEFENSEGAME_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere) class UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere) class UProjectileMovementComponent* ProjectileComp;
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	class ATower* Tower;
	class AEnemy* Enemy;

	float Speed = 2000.f;
	float Damage = 2.f;
	float Interal = 0.2f;

	virtual void TransferDamage();
	UFUNCTION() void HitEnemy(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
