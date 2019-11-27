// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Explode.generated.h"

UCLASS()
class TOWERDEFENSEGAME_API AExplode : public AActor
{
	GENERATED_BODY()
	
public:	
	AExplode();

	UPROPERTY(VisibleAnywhere) class USceneComponent* RootComp;
	UPROPERTY(VisibleAnywhere) class USphereComponent* SphereComp;

	class ATower* Tower;
	float Damage = 0.f;
	float Range = 0.f;

	void OnConstruction(const FTransform& Transform) override;

	UFUNCTION() void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

protected:
	virtual void BeginPlay() override;
};
