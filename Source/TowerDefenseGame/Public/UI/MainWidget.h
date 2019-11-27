// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <ProgressBar.h>
#include <TextBlock.h>
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSEGAME_API UMainWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	class ATDGameMode* GameMode;

	UProgressBar* Bar;
	UTextBlock* Text_Total;
	UTextBlock* Text_Destroyed;
	UTextBlock* Text_Spawned;

	UFUNCTION() float GetBaseHP();
	UFUNCTION() FText GetTotalEnemyNum();
	UFUNCTION() FText GetDestroyedEnemyNum();
	UFUNCTION() FText GetSpawnedEnemyNum();

};
