// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy.h"
#include <ConstructorHelpers.h>
#include <Components/StaticMeshComponent.h>
#include <WidgetComponent.h>
#include <Components/SplineComponent.h>
#include "HPWidget.h"
#include "TDGameMode.h"
#include "Tower.h"
#include "Base.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MeshComp);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMeshAsset(TEXT("/Game/TDG/Meshs/Shape_NarrowCapsule.Shape_NarrowCapsule"));
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> MaterialAsset(TEXT("/Game/TDG/Meshs/Materials/M_Enemy.M_Enemy"));
	if (StaticMeshAsset.Succeeded())
	{
		MeshComp->SetStaticMesh(StaticMeshAsset.Object);
		if (MaterialAsset.Succeeded())
			MeshComp->SetMaterial(0, MaterialAsset.Object);
	}
	MeshComp->SetCollisionProfileName(TEXT("OverlapAll"));
	PivotComp = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));
	PivotComp->SetupAttachment(RootComponent);
	PivotComp->SetRelativeLocation(FVector(0.f, 0.f, 50.f));
	WidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
	WidgetComp->SetupAttachment(RootComponent);
	WidgetComp->SetRelativeLocation(FVector(0.f, 0.f, 150.f));
	WidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	WidgetComp->SetDrawSize(FVector2D(100.f, 20.f));

	DebuffComp = CreateDefaultSubobject<UDebuffComponent>(TEXT("DebuffComponent"));
	DebuffComp->OnActiveDelegate.BindUFunction(this, FName("OnActiveDebuff"));
	DebuffComp->TickDelegate.BindUFunction(this, FName("TickDebuff"));
	DebuffComp->OnDeactiveDelegate.BindUFunction(this, FName("OnDeactiveDebuff"));

	HP = MaxHP;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	HP = MaxHP;
	MatR = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/TDG/Meshs/Materials/M_Enemy.M_Enemy"));
	Mat0 = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/TDG/Meshs/Materials/M_Enemy2.M_Enemy2"));
	Mat1 = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/TDG/Meshs/Materials/M_Enemy3.M_Enemy3"));
	GameMode = Cast<ATDGameMode>(GetWorld()->GetAuthGameMode());

	if (UClass* WidgetClass = LoadClass<UUserWidget>(nullptr, TEXT("/Game/TDG/UMG/WBP_HP.WBP_HP_C")))
	{
		UHPWidget* Bar = CreateWidget<UHPWidget>(GetWorld()->GetFirstPlayerController(), WidgetClass);
		if (Bar)
		{
			Bar->Enemy = this;
			WidgetComp->SetWidget(Bar);
		}
	}
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	Speed = FMath::FInterpTo(Speed, TargetSpeed, DeltaTime, 5.f);
	if (Spline && !GameMode->OverState)
	{
		if (Odometer < Spline->GetSplineLength())
		{
			Odometer += Speed * DeltaTime;
			FVector TargetLocation = Spline->GetLocationAtDistanceAlongSpline(Odometer, ESplineCoordinateSpace::World);
			FRotator TargetRotatotion = Spline->GetRotationAtDistanceAlongSpline(Odometer, ESplineCoordinateSpace::World);
			SetActorLocationAndRotation(TargetLocation, TargetRotatotion);
		}
		else
		{
			if (!bArrived)
				ArrivedBase();
		}
	}
}

void AEnemy::ArrivedBase()
{
	bArrived = true;
	if (GameMode && GameMode->Base)
		GameMode->Base->GetDamage(this, Damage);
	Death();
}

void AEnemy::GetDamage(AActor* Attacker, float _Damage)
{
	HP -= _Damage;
	if (GameMode)
	{
		if (HP <= 0)
			Death();
	}
}

void AEnemy::Death()
{
	if (GameMode)
		GameMode->DestroyedEnemy();
	for (ATower* Tower : Towers)
		Tower->RemoveEnemy(this);
	Destroy();
}

void AEnemy::BeginSlow()
{
	MeshComp->SetMaterial(0, Mat0);
	TargetSpeed = SlowSpeed;
}

void AEnemy::EndSlow()
{
	TargetSpeed = NormalSpeed;
}

void AEnemy::BeginPoison()
{
	MeshComp->SetMaterial(0, Mat1);
}

void AEnemy::TickPoison(ADebuffTower* _Tower, float _DeltaTime)
{
	GetDamage(_Tower, 3.f*_DeltaTime);
}

void AEnemy::EndDebuff()
{
	UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *FString("EDebuff"), true);
	if (EnumPtr)
		for (int32 i = 0; i < EnumPtr->NumEnums(); i++)
		{
			EDebuff Debuff = (EDebuff)i;
			if (DebuffComp->GetIsActived(Debuff))
			{
				FString MaterialName = "Mat" + FString::FromInt(i);
				UMaterialInterface* MaterialPtr = FindObject<UMaterialInterface>(this, *MaterialName, true);
				if (MaterialPtr)
				{
					MeshComp->SetMaterial(0, MaterialPtr);
					return;
				}
			}
		}
	MeshComp->SetMaterial(0, MatR);
}

void AEnemy::SetDebuff(ADebuffTower* _Tower, float _Duration)
{
	DebuffComp->OnActiveDebuff(_Tower, _Duration);
}

bool AEnemy::GetDebuffState(EDebuff _Debuff)
{
	return DebuffComp->GetIsActived(_Debuff);
}

void AEnemy::OnActiveDebuff(ADebuffTower* _Tower)
{
	switch (_Tower->Debuff)
	{
	case EDebuff::Slow:
		BeginSlow();
		break;
	case EDebuff::Poison:
		BeginPoison();
		break;
	default:
		break;
	}
}

void AEnemy::TickDebuff(ADebuffTower* _Tower, float _DeltaTime)
{
	switch (_Tower->Debuff)
	{
	case EDebuff::Poison:
		TickPoison(_Tower, _DeltaTime);
		break;
	default:
		break;
	}
}

void AEnemy::OnDeactiveDebuff(ADebuffTower* _Tower)
{
	switch (_Tower->Debuff)
	{
	case EDebuff::Slow:
		EndDebuff();
		EndSlow();
		break;
	case EDebuff::Poison:
		EndDebuff();
		break;
	default:
		break;
	}
}

