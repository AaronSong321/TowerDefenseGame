// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UObject/NameTypes.h"
#include "DataType.h"
#include "DebuffTower.h"
#include "DebuffComponent.generated.h"

DECLARE_DELEGATE_OneParam(Delegate_OnActive, ADebuffTower*)
DECLARE_DELEGATE_TwoParams(Delegate_Tick, ADebuffTower*, float)
DECLARE_DELEGATE_OneParam(Delegate_OnDeactive, ADebuffTower*)

struct SDebuffState
{
	class ADebuffTower* DebuffTower;
	EDebuff Debuff;
	bool IsActived = false;
	float Duration = 0;
	float CurrentTime = 0;

	SDebuffState() :Debuff(EDebuff::Slow){};
	SDebuffState(EDebuff _Debuff) :Debuff(_Debuff){};

};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOWERDEFENSEGAME_API UDebuffComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDebuffComponent();
	AEnemy* Enemy;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void OnActiveDebuff(ADebuffTower* _Tower, float _Duration);
	SDebuffState* GetStateFromTable(EDebuff _Debuff);

	TArray<SDebuffState*> GetAllActivedDebuff();
	bool GetIsActived(EDebuff _Debuff);
	bool bInstant;
	FName UniqueDebuffName;
	Delegate_OnActive OnActiveDelegate;
	Delegate_Tick TickDelegate;
	Delegate_OnDeactive OnDeactiveDelegate;

private:
	TArray<SDebuffState> DebuffTable;
	void InitializeDebuffTable();
	void TickDebuff(ADebuffTower* _Tower, float _DeltaTime);
	void OnDeactiveDebuff(ADebuffTower* _Tower);

};
