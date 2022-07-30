// Fill out your copyright notice in the Description page of Project Settings.
//this is player , wall , key and all other stuff dont miss dont forget ya ana XD i dont want to re do the project again
#pragma once

#include "CoreMinimal.h"
#include "GameObject.h"
#include "GamePlayObject.generated.h"

/**
 * 
 */
UCLASS()
class RULEBENDER_API AGamePlayObject : public AGameObject
{
	GENERATED_BODY()

	AGamePlayObject();

	virtual void BeginPlay() override;

	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category="Custom Variables")
	EObjectType ObjectType;//used to define what object to be controled with the rule

	UPROPERTY(EditAnywhere, BlueprintReadWrite ,Category="Custom Variables")
	TMap<ERule, bool> RulesStates;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Custom Variables")
	TEnumAsByte<EDrawDebugTrace::Type> DrawMovementDebug;
	
	
	  bool MoveToGrid(FVector Direction) override;

	  void SetObjectPropertiseByStates() override;

	  UFUNCTION()
	  void ReactToInput(FVector& Direction);

	  bool IsRuleActive(ERule RuleState);

	  float GetMovementLayer();
};
