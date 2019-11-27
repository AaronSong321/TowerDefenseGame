// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actors/Tower.h"
#include "DebuffTower.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSEGAME_API ADebuffTower : public ATower
{
	GENERATED_BODY()

public:
	ADebuffTower();

	bool GetTarget() override;

	EDebuff Debuff;
	
};
