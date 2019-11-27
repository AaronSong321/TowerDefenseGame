// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Waypoint.h"
#include <Button.h>
#include <WidgetSwitcher.h>
#include "OptionsWidget.generated.h"

/**
 * 
 */

UCLASS()
class TOWERDEFENSEGAME_API UOptionsWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:
	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	UFUNCTION() void Open(AWaypoint* _Waypoint);
	UFUNCTION() void Close();
	UFUNCTION() void SwitchPanel();

	UButton* Btn_Rife;
	UButton* Btn_Cannon;
	UButton* Btn_Slow;
	UButton* Btn_Poison;
	UButton* Btn_Destroy;
	UWidgetSwitcher* Switcher;

	class AWaypoint* Waypoint;
	FVector2D MousePosition;
	UFUNCTION() void OnClicked_Rife();
	UFUNCTION() void OnClicked_Cannon();
	UFUNCTION() void OnClicked_Slow();
	UFUNCTION() void OnClicked_Poison();
	UFUNCTION() void OnClicked_Destroy();

};
