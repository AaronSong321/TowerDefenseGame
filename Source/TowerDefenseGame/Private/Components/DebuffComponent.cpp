// Fill out your copyright notice in the Description page of Project Settings.

#include "DebuffComponent.h"
#include <UObjectGlobals.h>
#include "Enemy.h"
#include "DebuffTower.h"

// Sets default values for this component's properties
UDebuffComponent::UDebuffComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	
	InitializeDebuffTable();

}


// Called when the game starts
void UDebuffComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	Enemy = Cast<AEnemy>(GetOwner());

}


// Called every frame
void UDebuffComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *FString("EDebuff"), true);
	if (EnumPtr)
		for (int32 i = 0; i < EnumPtr->NumEnums(); i++)
		{
			EDebuff Debuff = (EDebuff)i;
			ADebuffTower* Tower = GetStateFromTable(Debuff)->DebuffTower;
			if (Tower)
				TickDebuff(Tower, DeltaTime);
		}

}

void UDebuffComponent::InitializeDebuffTable()
{
	UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *FString("EDebuff"), true);
	if (EnumPtr)
		for (int32 i = 0; i < EnumPtr->NumEnums(); i++)
		{
			EDebuff Debuff = (EDebuff)i;
			DebuffTable.Add(SDebuffState(Debuff));
		}
}

void UDebuffComponent::OnActiveDebuff(ADebuffTower* _Tower, float _Duration)
{
	SDebuffState* DebuffState = GetStateFromTable(_Tower->Debuff);
	if (DebuffState)
	{
		DebuffState->DebuffTower = _Tower;
		DebuffState->IsActived = true;
		DebuffState->CurrentTime = 0;
		DebuffState->Duration = _Duration;
	}

	OnActiveDelegate.ExecuteIfBound(_Tower);

}

void UDebuffComponent::TickDebuff(ADebuffTower* _Tower, float _DeltaTime)
{
	SDebuffState* Debuff = GetStateFromTable(_Tower->Debuff);
	if (Debuff)
	{
		if (Debuff->IsActived == false)
			return;

		TickDelegate.ExecuteIfBound(_Tower, _DeltaTime);
		Debuff->CurrentTime += _DeltaTime;
		if (Debuff->CurrentTime >= Debuff->Duration)
			OnDeactiveDebuff(Debuff->DebuffTower);
	}
}

void UDebuffComponent::OnDeactiveDebuff(ADebuffTower* _Tower)
{
	SDebuffState* DebuffState = GetStateFromTable(_Tower->Debuff);
	if (DebuffState)
	{
		DebuffState->DebuffTower = nullptr;
		DebuffState->IsActived = false;
		DebuffState->CurrentTime = 0;
		DebuffState->Duration = 0;
	}

	OnDeactiveDelegate.ExecuteIfBound(_Tower);

}

SDebuffState* UDebuffComponent::GetStateFromTable(EDebuff _Debuff)
{
	for (SDebuffState& DebuffState:DebuffTable)
		if (DebuffState.Debuff == _Debuff)
			return &DebuffState;
	return nullptr;
}

TArray<SDebuffState*> UDebuffComponent::GetAllActivedDebuff()
{
	TArray<SDebuffState*> ActivedDebuffs;
	for (SDebuffState& DebuffState : DebuffTable)
		if (DebuffState.IsActived == true)
			ActivedDebuffs.Add(&DebuffState);
	return ActivedDebuffs;
}

bool UDebuffComponent::GetIsActived(EDebuff _Debuff)
{
	return GetStateFromTable(_Debuff)->IsActived;
}
