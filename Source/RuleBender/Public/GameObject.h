// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// this class will act like the player or the other objects except the rule object
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BinderStatics.h"
#include "GameObject.generated.h"

class UPaperSpriteComponent;

UCLASS()
class RULEBENDER_API AGameObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
public:

	UPROPERTY(VisibleAnywhere, Category="Custom Components")
	USceneComponent* newRoot;

	UPROPERTY(VisibleAnywhere, Category="Custom Components")
	UPaperSpriteComponent* SpriteComponent;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//shared functions between all objects
	virtual bool MoveToGrid(FVector Direction);//each class will have it's own implementation

	void SetCollisionState(bool IsActive);

	virtual void SetObjectPropertiseByStates();// called in begin play to initilaize propertise and implemented in the childs 
	

};
