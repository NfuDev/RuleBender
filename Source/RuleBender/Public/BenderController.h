// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BenderController.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FButtonPressed, FVector&, Direction);
UCLASS()
class RULEBENDER_API ABenderController : public APlayerController
{
	GENERATED_BODY()

	

	public:
	
	FButtonPressed ButtonPressed;
	virtual void SetupInputComponent() override;
	
	//Event to boradcast the delegate
	void BroadcastDelegate(FVector& Direction);
	
	//funcions to call by the inputs to call the delegate events
	void Input_UP();
	void Input_Down();
	void Input_Right();
	void Input_Left();
	
};
