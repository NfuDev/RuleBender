// Fill out your copyright notice in the Description page of Project Settings.


#include "BinderStatics.h"

#include "Kismet/KismetSystemLibrary.h"

BinderStatics::BinderStatics()
{
}

BinderStatics::~BinderStatics()
{
}

void BinderStatics::CheckGrids(AActor* Context,float x_dir, float y_dir, FHitResult& X_HitResult, FHitResult& Y_HitResult, EDrawDebugTrace::Type DrawDebugType)
{
	FVector DirectionX = FVector::ZeroVector; DirectionX.X = x_dir;
	FVector DirectionY = FVector::ZeroVector; DirectionY.Y = y_dir;

	FVector Start = Context->GetActorLocation();
	FVector EndX = Start + DirectionX * 100;
	FVector EndY = Start + DirectionY * 100;
	
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypeArray;
	ObjectTypeArray.Add(EObjectTypeQuery::ObjectTypeQuery7);
	TArray<AActor*> ActorsToIgnore;
	

	UKismetSystemLibrary::SphereTraceSingleForObjects(Context, Start, EndX, 1.0f, ObjectTypeArray, false,ActorsToIgnore,
		DrawDebugType,  X_HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f);

	UKismetSystemLibrary::SphereTraceSingleForObjects(Context, Start, EndY, 1.0f, ObjectTypeArray, false,ActorsToIgnore,
		DrawDebugType,  Y_HitResult, true, FLinearColor::Red, FLinearColor::Green, 5.0f);
	
}

