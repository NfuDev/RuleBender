// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePlayClasses/BaseRule.h"

#include "PaperSpriteComponent.h"
#include "GamePlayClasses/GamePlayObject.h"
#include "Kismet/GameplayStatics.h"
#include "VisualLogger/VisualLoggerTypes.h"

void ABaseRule::BeginPlay()
{
	Super::BeginPlay();

}

bool ABaseRule::MoveToGrid(FVector Direction)
{
	FVector Start = GetActorLocation();
	Start.Z = 0.1;
	FVector newLocation = Start + Direction* 100;
	
	FHitResult Xhit;
	FHitResult YHit;
	
	BinderStatics::CheckGrids(this, Direction.X, Direction.Y, Xhit, YHit, DrawMovementDebug);//trace before moving
	
	FHitResult CheckResults = FMath::Abs(Direction.X) > FMath::Abs(Direction.Y) ? Xhit : YHit;
	if(!CheckResults.bBlockingHit)
	{
		//after the trace bfore moving we move if we did not find anythig in the way and then trace for near by activators 
		SetActorLocation(newLocation);
		CheckForActivator();//trace for near by activators
		return true;
	}
	
	else if(CheckResults.bBlockingHit)
	{
		//searching for game objects to push if found 
		AGameObject* DetectedObject = Cast<AGameObject>(CheckResults.GetActor());
		if(CheckResults.GetActor())
		{
			if(DetectedObject->MoveToGrid(Direction))
			{
				SetActorLocation(newLocation);
			    CheckForActivator();
				return true;
			}
		}

	}
	return false;
}


void ABaseRule::CheckForActivator()
{
	FHitResult Xhit;
	FHitResult YHit;

	int x_dir = 1;
	int y_dir = 1;

	switch (ObjectTag)
	{
	case EObjectTag::Rule :
		{
			x_dir = -1;
			y_dir = -1;
			break;
		}
		
	case EObjectTag::Activator :
		{
			x_dir = 1;
			y_dir = 1;
			break;
		}
		
	case EObjectTag::Effector :
		{
			x_dir = 1;
			y_dir = 1;
			break;
		}
		
	case EObjectTag::GameObject :
		{
			x_dir = 1;
			y_dir = 1;
			break;
		}

	}
	
	BinderStatics::CheckGrids(this, x_dir, y_dir, Xhit, YHit, DrawActivatorDebug);
	if(Xhit.bBlockingHit)
	{
		if(ObjectTag == EObjectTag::Rule || ObjectTag == EObjectTag::Effector)
		{
			IfFoundActivator(Xhit);
			if(Activator_x)
			{
				Activator_x->CheckRuleSequence();
			}

			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "should Activate On X");
			}
		}
		if(ObjectTag == EObjectTag::Activator)
		{
			IfFoundRuleOrEffector(Xhit);
		}
	}

	if(!Xhit.bBlockingHit)
	{
		if(Activator_x && ObjectTag != EObjectTag::Activator)
		{
			Activator_x->CheckRuleSequence();
		}

		if(ObjectTag == EObjectTag::Activator)
		{
			CheckRuleSequence();
		}
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, " should Deactivate On X");
		}
	}

	if(YHit.bBlockingHit)
	{
		if(ObjectTag == EObjectTag::Rule || ObjectTag == EObjectTag::Effector)
		{
			IfFoundActivator(YHit);
			if(Activator_y)
			{
				Activator_y->CheckRuleSequence();
			}
		}
		if(ObjectTag == EObjectTag::Activator)
		{
			IfFoundRuleOrEffector(YHit);
		}
	}

	if(!YHit.bBlockingHit)
	{
		if(Activator_y && ObjectTag != EObjectTag::Activator)
		{
			Activator_y->CheckRuleSequence();
		}
		if(ObjectTag == EObjectTag::Activator)
		{
			CheckRuleSequence();
		}
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, "should Deactivate On Y");
		}
	}
	
}


void ABaseRule::CheckRuleSequence()
{

	  FHitResult RHit;
	  FHitResult LHit;
	  FHitResult UHit;
	  FHitResult DHit;

	  BinderStatics::CheckGrids(this, 1, 1, RHit, DHit, DrawSequneceDebug);
	  BinderStatics::CheckGrids(this, -1, -1, LHit, UHit, DrawSequneceDebug);

	  ABaseRule* Rule_x = Cast<ABaseRule>(RHit.GetActor());
	  ABaseRule* Effector_x = Cast<ABaseRule>(LHit.GetActor());
	  ABaseRule* Rule_y = Cast<ABaseRule>(DHit.GetActor());
   	  ABaseRule* Effector_y = Cast<ABaseRule>(UHit.GetActor());

	if(Rule_x && Effector_x)
    {
		ActivatedRule_X = Rule_x;
		Rule_x->X_TargetedTypes = Effector_x->AffectedTypes;
		Rule_x->Activator_x = this;
		Effector_x->Activator_x = this;
		Rule_x->ActivateRuleForType(Rule_x->X_TargetedTypes, true);
	
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "Rule Activated On X"); 
			}	
	}
	else if(!Rule_x || !Effector_x)
	{
		if(ActivatedRule_X)
		{
			ActivatedRule_X->ActivateRuleForType(ActivatedRule_X->X_TargetedTypes, false);
			ActivatedRule_X = nullptr;
		}
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, "Deactivated On X"); 
		}
	}
	if(Rule_y && Effector_y)
	{
		ActivatedRule_Y = Rule_y;
		Rule_y->Y_TargetedTypes = Effector_y->AffectedTypes;
		Rule_y->Activator_y = this;
		Effector_y->Activator_y = this;
		Rule_y->ActivateRuleForType(Rule_y->Y_TargetedTypes, true);
	
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "Rule Activated On Y"); 
		}	
	}
	else if(!Rule_y || !Effector_y)
	{
		if(ActivatedRule_Y)
		{
			ActivatedRule_Y->ActivateRuleForType(ActivatedRule_Y->Y_TargetedTypes, false);
			ActivatedRule_Y = nullptr;
		}
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, " Deactivated On Y"); 
		}
	}

}



void ABaseRule::ActivateRuleForType(EObjectType TargetType,bool IsActive)
{
	
	TArray<AActor*> FoundActors;
	TArray<AGamePlayObject*> GameObjects;
	
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGameObject::StaticClass(), FoundActors);
	
	//filter for GameObject
	for (AActor* Actor : FoundActors)
	{
		AGamePlayObject* GameObject = Cast<AGamePlayObject>(Actor);
		if(GameObject)
		{
			GameObjects.Add(GameObject);
		}
	}

	//filter game objects for target type
	for(AGamePlayObject* GameObject : GameObjects)
	{
		if(GameObject->ObjectType == TargetType)
		{
			GameObject->RulesStates[Rule] = IsActive;
			GameObject->SetCollisionState(IsActive);// i will need to find a better way to do this later 
		}
	}
}


void ABaseRule::IfFoundActivator(FHitResult HitResult)
{
	ABaseRule* Activator = Cast<ABaseRule>(HitResult.GetActor());

	if(Activator && Activator->ObjectTag == EObjectTag::Activator)
	{
		Activator->CheckRuleSequence();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, "Found Activator"); 
		}
		
	}
}

void ABaseRule::IfFoundRuleOrEffector(FHitResult HitResult)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Blue, "Activator pushed");
	}
	
	ABaseRule* Rule_Effector = Cast<ABaseRule>(HitResult.GetActor());
	if(Rule_Effector)
	{
		if(Rule_Effector->ObjectTag == EObjectTag::Rule || Rule_Effector->ObjectTag == EObjectTag::Effector)
		{
			CheckRuleSequence();
		}
	}
}