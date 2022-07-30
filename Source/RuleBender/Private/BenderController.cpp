// Fill out your copyright notice in the Description page of Project Settings.


#include "BenderController.h"

void ABenderController::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("Right", IE_Pressed, this, &ABenderController::Input_Right);
	InputComponent->BindAction("Left", IE_Pressed, this, &ABenderController::Input_Left);
	InputComponent->BindAction("UP", IE_Pressed, this, &ABenderController::Input_UP);
	InputComponent->BindAction("Down", IE_Pressed, this, &ABenderController::Input_Down);
	
}

void ABenderController::BroadcastDelegate(FVector& Direction)
{
	ButtonPressed.Broadcast(Direction);
}

void ABenderController::Input_UP()
{
	FVector Direction = {0.0f,-1.0f,0.0f};
	BroadcastDelegate(Direction);
}

void ABenderController::Input_Down()
{
	FVector Direction = {0.0f,1.0f,0.0f};
	BroadcastDelegate(Direction);
}

void ABenderController::Input_Right()
{
	FVector Direction = {1.0f,0.0f,0.0f};
	BroadcastDelegate(Direction);
}

void ABenderController::Input_Left()
{
	FVector Direction = {-1.0f,0.0f,0.0f};
	BroadcastDelegate(Direction);
}
