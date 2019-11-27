// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include <ProgressBar.h>
#include "Enemy.h"
#include "HPWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOWERDEFENSEGAME_API UHPWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
public:
	UProgressBar* Bar;
	UFUNCTION() float GetPercent();
	class AEnemy* Enemy;

};
