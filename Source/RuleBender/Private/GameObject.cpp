// Fill out your copyright notice in the Description page of Project Settings.

#include "RuleBender/Public/GameObject.h"


#include "Paper2D/Classes/PaperSpriteComponent.h"


// Sets default values
AGameObject::AGameObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	newRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	newRoot->SetRelativeLocationAndRotation(FVector::ZeroVector, FRotator::ZeroRotator);
	
	SetRootComponent(newRoot);
	
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite Component"));
	SpriteComponent->SetupAttachment(GetRootComponent());
	
	
	SpriteComponent->SetWorldRotation(FRotator(0.0f,0.0f,-90.0f));

}

// Called when the game starts or when spawned
void AGameObject::BeginPlay()
{
	Super::BeginPlay();
	SpriteComponent->SetCollisionObjectType(ECC_GameTraceChannel1);//make sure that we have the right collision setup for the traces to work

}

// Called every frame
void AGameObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGameObject::MoveToGrid(FVector Direction)
{
	return false;
}

void AGameObject::SetCollisionState(bool IsActive)
{
	ECollisionEnabled::Type CollisionEnabled = IsActive ? ECollisionEnabled::QueryAndPhysics : ECollisionEnabled::NoCollision;
	SpriteComponent->SetCollisionEnabled(CollisionEnabled);
}

void AGameObject::SetObjectPropertiseByStates()
{
	
}

