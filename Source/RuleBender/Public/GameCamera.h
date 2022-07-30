// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameCamera.generated.h"

class UCameraComponent;

UCLASS()
class RULEBENDER_API AGameCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera settings")
	float CameraDistance;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Custom Component")
	UCameraComponent* GameCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Custom Component")
	USceneComponent* NewRoot;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
