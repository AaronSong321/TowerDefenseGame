// Fill out your copyright notice in the Description page of Project Settings.

#include "OptionsWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetLayoutLibrary.h"
#include <CanvasPanelSlot.h>
#include <SViewport.h>
#include <ScriptDelegates.h>
#include "DataType.h"

void UOptionsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Rife = Cast<UButton>(GetWidgetFromName(FName(TEXT("Btn_Rife"))));
	Btn_Cannon = Cast<UButton>(GetWidgetFromName(FName(TEXT("Btn_Cannon"))));
	Btn_Slow = Cast<UButton>(GetWidgetFromName(FName(TEXT("Btn_Slow"))));
	Btn_Poison = Cast<UButton>(GetWidgetFromName(FName(TEXT("Btn_Poison"))));
	Btn_Destroy = Cast<UButton>(GetWidgetFromName(FName(TEXT("Btn_Destroy"))));
	Switcher = Cast<UWidgetSwitcher>(GetWidgetFromName(FName(TEXT("Switcher"))));

	FScriptDelegate Del_Rife;
	Del_Rife.BindUFunction(this, "OnClicked_Rife");
	Btn_Rife->OnClicked.Add(Del_Rife);
	FScriptDelegate Del_Cannon;
	Del_Cannon.BindUFunction(this, "OnClicked_Cannon");
	Btn_Cannon->OnClicked.Add(Del_Cannon);
	FScriptDelegate Del_Slow;
	Del_Slow.BindUFunction(this, "OnClicked_Slow");
	Btn_Slow->OnClicked.Add(Del_Slow);
	FScriptDelegate Del_Poison;
	Del_Poison.BindUFunction(this, "OnClicked_Poison");
	Btn_Poison->OnClicked.Add(Del_Poison);
	FScriptDelegate Del_Destroy;
	Del_Destroy.BindUFunction(this, "OnClicked_Destroy");
	Btn_Destroy->OnClicked.Add(Del_Destroy);

}

void UOptionsWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	GEngine->GameViewport->GetMousePosition(MousePosition);
	FGeometry Geometry = GEngine->GetGameViewportWidget()->GetCachedGeometry();
	FVector2D AbsCood = (Geometry.LocalToAbsolute(MousePosition));
	bool bResult = MyGeometry.IsUnderLocation(AbsCood);
	if (!bResult)
		Close();
}

void UOptionsWidget::Open(AWaypoint* _Waypoint)
{
	Waypoint = _Waypoint;
	GEngine->GameViewport->GetMousePosition(MousePosition);
	FVector2D SpawnPoint = MousePosition - 10.f;
	SetPositionInViewport(SpawnPoint);
	SwitchPanel();
	SetVisibility(ESlateVisibility::Visible);
}

void UOptionsWidget::Close()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UOptionsWidget::SwitchPanel()
{
	if (Waypoint)
	{
		Switcher->SetActiveWidgetIndex(Waypoint->bHasTower ? 1 : 0);
		Cast<UCanvasPanelSlot>(Switcher->Slot)->SetSize(FVector2D(300.f, Waypoint->bHasTower ? 80.f : 320.f));
	}
}

void UOptionsWidget::OnClicked_Rife()
{
	if (Waypoint)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Rife"));
		Waypoint->SpawnTower(ETower::Rife);
		Close();
	}
}

void UOptionsWidget::OnClicked_Cannon()
{
	if (Waypoint)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Cannon"));
		Waypoint->SpawnTower(ETower::Cannon);
		Close();
	}
}

void UOptionsWidget::OnClicked_Slow()
{
	if (Waypoint)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Slow"));
		Waypoint->SpawnTower(ETower::Slow);
		Close();
	}
}

void UOptionsWidget::OnClicked_Poison()
{
	if (Waypoint)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Poison"));
		Waypoint->SpawnTower(ETower::Poison);
		Close();
	}
}


void UOptionsWidget::OnClicked_Destroy()
{
	if (Waypoint)
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, TEXT("Destroy"));
		Waypoint->DestroyTower();
		Close();
	}
}

