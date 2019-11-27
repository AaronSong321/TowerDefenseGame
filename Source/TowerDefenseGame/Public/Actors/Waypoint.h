// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tower.h"
#include "DataType.h"
#include "Waypoint.generated.h"

UCLASS()
class TOWERDEFENSEGAME_API AWaypoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AWaypoint();

	UPROPERTY(VisibleAnywhere) UStaticMeshComponent* MeshComp;
	UPROPERTY(VisibleAnywhere) USceneComponent* SpawnPointComp;

protected:
	virtual void BeginPlay() override;

public:
	class ATDGameMode* GameMode;
	class ATower* Tower;
	bool bHasTower;
	UFUNCTION() void OpenUI_Options();
	void SpawnTower(ETower::Type);
	void DestroyTower();

};
