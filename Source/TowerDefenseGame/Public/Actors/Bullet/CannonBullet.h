// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Bullet.h"
#include "CannonBullet.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSEGAME_API ACannonBullet : public ABullet
{
	GENERATED_BODY()
	
public:
	ACannonBullet();

	void TransferDamage() override;
	float Range = 200.f;
};
