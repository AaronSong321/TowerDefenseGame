// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Bullet.h"
#include "DataType.h"
#include "DebuffBullet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSEGAME_API ADebuffBullet : public ABullet
{
	GENERATED_BODY()
	
public:
	ADebuffBullet();

	void TransferDamage() override;

	EDebuff Debuff;
	float Duration;
};
