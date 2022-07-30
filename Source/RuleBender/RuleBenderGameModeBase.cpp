// Copyright Epic Games, Inc. All Rights Reserved.


#include "RuleBenderGameModeBase.h"

#include "BenderController.h"

ARuleBenderGameModeBase::ARuleBenderGameModeBase()
{
	DefaultPawnClass = nullptr;
	PlayerControllerClass = ABenderController::StaticClass();
}
