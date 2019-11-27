// Fill out your copyright notice in the Description page of Project Settings.

#include "MainWidget.h"
#include "Base.h"

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

	GameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode());

	Bar = Cast<UProgressBar>(GetWidgetFromName(FName(TEXT("Bar"))));
	Text_Total = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Text_Total"))));
	Text_Destroyed = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Text_Destroyed"))));
	Text_Spawned = Cast<UTextBlock>(GetWidgetFromName(FName(TEXT("Text_Spawned"))));

	Bar->PercentDelegate.BindUFunction(this, "GetBaseHP");
	Bar->SynchronizeProperties();
	Text_Total->TextDelegate.BindUFunction(this, "GetTotalEnemyNum");
	Text_Total->SynchronizeProperties();
	Text_Destroyed->TextDelegate.BindUFunction(this, "GetDestroyedEnemyNum");
	Text_Destroyed->SynchronizeProperties();
	Text_Spawned->TextDelegate.BindUFunction(this, "GetSpawnedEnemyNum");
	Text_Spawned->SynchronizeProperties();

}

float UMainWidget::GetBaseHP()
{
	if (GameMode && GameMode->Base)
		return GameMode->Base->HP / GameMode->Base->MaxHP;
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("GameMode or Base is invalid!"));
	return 0.f;
}

FText UMainWidget::GetTotalEnemyNum()
{
	if (GameMode)
		return FText::FromString(FString::FromInt(GameMode->TotalEnemyNum));
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("GameMode is invalid!"));
	return FText::FromString("0");
}

FText UMainWidget::GetDestroyedEnemyNum()
{
	if (GameMode)
		return FText::FromString(FString::FromInt(GameMode->DestroyedEnemyNum));
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("GameMode is invalid!"));
	return FText::FromString("0");
}

FText UMainWidget::GetSpawnedEnemyNum()
{
	if (GameMode)
		return FText::FromString(FString::FromInt(GameMode->SpawnedEnemyNum));
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("GameMode is invalid!"));
	return FText::FromString("0");
}
