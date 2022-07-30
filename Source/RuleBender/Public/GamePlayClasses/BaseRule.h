// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameObject.h"
#include "BaseRule.generated.h"

/**
 * 
 */
UCLASS()
class RULEBENDER_API ABaseRule : public AGameObject
{
	GENERATED_BODY()

	public:
    // General Propertise:
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Custom Variables")
	EObjectTag ObjectTag;

	void CheckForActivator();//used to find activator grid and if found the search for a valid rule sequence to activate a rule

	bool MoveToGrid(FVector Direction) override;// to move the game object to next grid

	void BeginPlay() override;

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Custom Variables")
	TEnumAsByte<EDrawDebugTrace::Type> DrawMovementDebug;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Custom Variables")
	TEnumAsByte<EDrawDebugTrace::Type> DrawActivatorDebug;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Custom Variables")
	TEnumAsByte<EDrawDebugTrace::Type> DrawSequneceDebug;

	
	//Rules Specific Propertise
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (EditCondition = "ObjectTag == EObjectTag::Rule", EditConditionHides),Category="Custom Variables")
	ERule Rule;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="testing")
	EObjectType X_TargetedTypes;
	
	UPROPERTY()
	EObjectType Y_TargetedTypes;

	void ActivateRuleForType(EObjectType TargetType,bool IsActive);

	void IfFoundActivator(FHitResult HitResult);
	
//maybe i will delete those
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Custom Variables")
	ABaseRule* Activator_x;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Custom Variables")
	ABaseRule* Activator_y;

	

	//if tag was activator these are the variables for it's logic i dont want to make a new class for it

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Custom variables")
	ABaseRule* ActivatedRule_X;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Custom variables")//just for debugging i should change the property to not be refelected in the editor
	ABaseRule* ActivatedRule_Y;

	void CheckRuleSequence();

	void IfFoundRuleOrEffector(FHitResult HitResult);

	//effector specific properties:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta = (EditCondition = "ObjectTag == EObjectTag::Effector", EditConditionHides),Category="Custom Variables")
	EObjectType AffectedTypes;
	

	
	
};
