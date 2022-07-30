// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Kismet/KismetSystemLibrary.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class EObjectTag : uint8
{
	GameObject = 0,
	Rule = 1,
	Activator = 2,
	Effector = 3,
};

UENUM(BlueprintType)
enum class EObjectType : uint8
{
	Player = 0,
	Wall = 1,
	Key = 2,
	Fire = 3,
};
UENUM(BlueprintType)
enum class ERule : uint8
{
	IsYou = 0,
	IsPush = 1,
	IsWin = 2,
	IsLose = 3,
	IsStop = 4,
};
class RULEBENDER_API BinderStatics
{
public:
	BinderStatics();
	~BinderStatics();

	static void CheckGrids(AActor* Context, float x_dir, float y_dir, FHitResult& X_HitResult, FHitResult& Y_HitResult, EDrawDebugTrace::Type DrawDebugType);
	
};
