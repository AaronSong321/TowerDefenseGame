// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TDPawn.generated.h"

UCLASS()
class TOWERDEFENSEGAME_API ATDPawn : public APawn
{
	GENERATED_BODY()

public:
	ATDPawn();
	UPROPERTY(VisibleAnywhere) class USpringArmComponent* SpringArmComp;
	UPROPERTY(VisibleAnywhere) class UCameraComponent* CameraComp;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
