// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayClasses/GamePlayObject.h"

#include "AIController.h"
#include "BenderController.h"
#include "BinderStatics.h"
#include "GamePlayClasses/BaseRule.h"
#include "Kismet/GameplayStatics.h"

AGamePlayObject::AGamePlayObject()
{
	//fill rules
	RulesStates.Add(ERule::IsYou , false);
	RulesStates.Add(ERule::IsPush , false);
	RulesStates.Add(ERule::IsWin , false);
	RulesStates.Add(ERule::IsLose , false);
	RulesStates.Add(ERule::IsStop , false);

	
	
}

void AGamePlayObject::BeginPlay()
{
	Super::BeginPlay();
	
	//Bind Inputs to Movement
	ABenderController* BenderController = Cast<ABenderController>((UGameplayStatics::GetPlayerController(this, 0)));
	BenderController->ButtonPressed.AddDynamic(this, &AGamePlayObject::ReactToInput);

	SetObjectPropertiseByStates();
}

float AGamePlayObject::GetMovementLayer()
{
	
	float layer = IsRuleActive(ERule::IsStop) ? 0 : 0.1;

	return layer;
}

bool AGamePlayObject::MoveToGrid(FVector Direction)
{
		FVector Start = GetActorLocation();
	    Start.Z = GetMovementLayer();
		FVector newLocation = Start + Direction* 100;
	
		FHitResult Xhit;
		FHitResult YHit;
	
		BinderStatics::CheckGrids(this, Direction.X, Direction.Y, Xhit, YHit, DrawMovementDebug);
		FHitResult CheckResults = FMath::Abs(Direction.X) > FMath::Abs(Direction.Y) ? Xhit : YHit;
		if(!CheckResults.bBlockingHit)
		{
			SetActorLocation(newLocation);
			return true;
		}
	
		else if(CheckResults.bBlockingHit)
		{
			//searching for game objects to push if found 
			AGamePlayObject* DetectedObject = Cast<AGamePlayObject>(CheckResults.GetActor());

			//if the next grid is movable 
			if(DetectedObject && DetectedObject->IsRuleActive(ERule::IsPush) && !DetectedObject->IsRuleActive(ERule::IsStop))//
			{
				//check the next to it if also movable
				if(DetectedObject->MoveToGrid(Direction))
				{
					SetActorLocation(newLocation);
					return true;
				}
			}

			if(DetectedObject && !DetectedObject->IsRuleActive(ERule::IsPush) && !DetectedObject->IsRuleActive(ERule::IsStop))
			{
				SetActorLocation(newLocation);
				return true;
			}
			//if no game object but a rule was found
			ABaseRule* DetectedRule = Cast<ABaseRule>(CheckResults.GetActor());
			if(DetectedRule && DetectedRule->MoveToGrid(Direction))
			{
				SetActorLocation(newLocation);
				return true;
			}

			return false;
		}
	
	
	
	return false;
}


void AGamePlayObject::ReactToInput(FVector& Direction)
{
	if(IsRuleActive(ERule::IsYou))
	{
		MoveToGrid(Direction);
	}
}

bool AGamePlayObject::IsRuleActive(ERule RuleState)
{
	if(RulesStates.Contains(RuleState))
	{
		return RulesStates[RuleState];
	}
	return false;
}


void AGamePlayObject::SetObjectPropertiseByStates()
{
	bool enableDetection = IsRuleActive(ERule::IsStop) || IsRuleActive(ERule::IsPush);
	
	SetCollisionState(enableDetection);
}
