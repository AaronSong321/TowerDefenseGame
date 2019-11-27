// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

UENUM()
namespace ETower
{
	enum Type
	{
		Rife,
		Cannon,
		Slow,
		Poison
	};
}

UENUM()
namespace EBullet
{
	enum Type
	{
		Rife,
		Cannon,
		Slow,
		Poison
	};
}

UENUM()
enum class EDebuff
{
	Slow = 0,
	Poison
};