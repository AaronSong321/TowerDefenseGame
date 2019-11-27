// Fill out your copyright notice in the Description page of Project Settings.

#include "TDPawn.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

// Sets default values
ATDPawn::ATDPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	if (SpringArmComp) {
		SpringArmComp->SetupAttachment(RootComponent);
		SpringArmComp->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
		SpringArmComp->TargetArmLength = 1000.f;
		SpringArmComp->bDoCollisionTest = false;
		CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
		if (CameraComp)
			CameraComp->SetupAttachment(SpringArmComp);
	}
}

// Called when the game starts or when spawned
void ATDPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATDPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATDPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

