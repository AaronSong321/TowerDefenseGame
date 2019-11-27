// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TDGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSEGAME_API ATDGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	ATDGameMode();

	void OpenUI_Options(class AWaypoint*);

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	class UOptionsWidget* UI_Options;
	class UMainWidget* UI_Main;
	class ABase* Base;

	int TotalEnemyNum = 100;
	int SpawnedEnemyNum = 0;
	int DestroyedEnemyNum = 0;

	bool BaseBeDestroyed = false;
	bool SpawnedAllEnemys();
	void SpawnedEnemy();
	void DestroyedEnemy();

	void GameStart();
	void GameOver();
	bool OverState = false;
	bool IsGameOver();
	bool IsVictory();
	
};
