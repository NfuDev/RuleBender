// Fill out your copyright notice in the Description page of Project Settings.


#include "GameCamera.h"

#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGameCamera::AGameCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	NewRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(NewRoot);
	
	GameCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Game Camera"));
	GameCamera->SetupAttachment(GetRootComponent());

	CameraDistance = 500.0f;
	GameCamera->SetWorldLocation(FVector(0.0f,0.0f, CameraDistance));
	GameCamera->SetWorldRotation(FRotator(-90.0f, -90.0f,0.0f));


}

// Called when the game starts or when spawned
void AGameCamera::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	PlayerController->SetViewTarget(this);
	
}

// Called every frame
void AGameCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

