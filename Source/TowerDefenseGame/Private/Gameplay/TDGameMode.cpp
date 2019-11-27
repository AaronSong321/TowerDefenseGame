// Fill out your copyright notice in the Description page of Project Settings.

#include "TDGameMode.h"
#include "TDPawn.h"
#include "TDController.h"
#include <Engine/Engine.h>
#include <DeclarativeSyntaxSupport.h>
#include <SWeakWidget.h>
#include "Base.h"
#include "Waypoint.h"
#include "OptionsWidget.h"
#include "MainWidget.h"

ATDGameMode::ATDGameMode()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PlayerControllerClass = ATDController::StaticClass();
	DefaultPawnClass = ATDPawn::StaticClass();
}

void ATDGameMode::OpenUI_Options(AWaypoint* _Waypoint)
{
	if (UI_Options)
		UI_Options->Open(_Waypoint);
}

void ATDGameMode::BeginPlay()
{
	if (UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/TDG/UMG/WBP_Options.WBP_Options_C")))
	{
		UI_Options = CreateWidget<UOptionsWidget>(GetWorld()->GetFirstPlayerController(), WidgetClass);
		if (UI_Options)
		{
			UI_Options->AddToViewport();
			UI_Options->Close();
		}
	}
	if (UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/TDG/UMG/WBP_Main.WBP_Main_C")))
	{
		UI_Main = CreateWidget<UMainWidget>(GetWorld()->GetFirstPlayerController(), WidgetClass);
		if (UI_Main)
			UI_Main->AddToViewport();
	}

	FTimerHandle DelayHandle;
	GetWorldTimerManager().SetTimer(DelayHandle, this, &ATDGameMode::GameStart, 0.2f, false);
}

void ATDGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!OverState && IsGameOver())
	{
		OverState = true;
		GameOver();
	}
		
}

bool ATDGameMode::SpawnedAllEnemys()
{
	return SpawnedEnemyNum >= TotalEnemyNum;
}

void ATDGameMode::SpawnedEnemy()
{
	SpawnedEnemyNum++;
}

void ATDGameMode::DestroyedEnemy()
{
	DestroyedEnemyNum++;
}

void ATDGameMode::GameStart()
{
	if (Base)
		Base->BeginSpawnEnemy();
}

void ATDGameMode::GameOver()
{
	if (Base)
		Base->EndSpawnEnemy();
	if (IsVictory())
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Victory!"));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Green, TEXT("Defeat!"));
	}
}

bool ATDGameMode::IsGameOver()
{
	return BaseBeDestroyed || DestroyedEnemyNum == TotalEnemyNum;
}

bool ATDGameMode::IsVictory()
{
	if (BaseBeDestroyed)
		return false;
	return true;
}
