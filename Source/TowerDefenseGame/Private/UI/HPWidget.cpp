// Fill out your copyright notice in the Description page of Project Settings.

#include "HPWidget.h"

void UHPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Bar = Cast<UProgressBar>(GetWidgetFromName(FName(TEXT("Bar"))));
	Bar->PercentDelegate.BindUFunction(this, "GetPercent");
	Bar->SynchronizeProperties();
}

float UHPWidget::GetPercent()
{
	if (Enemy)
		return Enemy->HP / Enemy->MaxHP;
	else
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, TEXT("Enemy is nullptr!"));
	return 0.f;
}
