// Fill out your copyright notice in the Description page of Project Settings.


#include "AttributeSetBase.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"


UAttributeSetBase::UAttributeSetBase()
{
	
}

void UAttributeSetBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Ack, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAttributeSetBase, AckPercent, COND_None, REPNOTIFY_Always);
}

void UAttributeSetBase::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Health, OldHealth);
}

void UAttributeSetBase::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, MaxHealth, OldMaxHealth);
}

void UAttributeSetBase::OnRep_Ack(const FGameplayAttributeData& OldAck)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Ack, OldAck);
}

void UAttributeSetBase::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, Armor, OldArmor);
}

void UAttributeSetBase::OnRep_AckPercent(const FGameplayAttributeData& OldAckPercent)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAttributeSetBase, AckPercent, OldAckPercent);
}

void UAttributeSetBase::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	// Compute the delta between old and new, if it is available
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	//// Get the Target actor, which should be our owner
	//AActor* TargetActor = nullptr;
	//AController* TargetController = nullptr;
	//ARPGCharacterBase* TargetCharacter = nullptr;
	//if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	//{
	    //TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
	    //TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
	//}

	if (Data.EvaluatedData.Attribute == GetAckAttribute())
	{
		float LocalDamageDone = 0.0f;
	    LocalDamageDone = GetDamage();
	    //SetAck(0.f);
	    if (LocalDamageDone > 0)
	    {
	        const float OldHealth = GetHealth();
	    	//UE_LOG(LogTemp,Warning,TEXT("FFFFFFFFF=%f"),LocalDamageDone);
	        SetHealth(FMath::Clamp(OldHealth - LocalDamageDone, 0.0f, GetMaxHealth()));
	    	onHealthChangeDelegate.Broadcast(Health.GetBaseValue(),MaxHealth.GetCurrentValue());
	    }
	}
	else if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Handle other health changes such as from healing or direct modifiers
		// First clamp it
		SetHealth(FMath::Clamp(GetHealth(), 0.0f, GetMaxHealth()));
		onHealthChangeDelegate.Broadcast(Health.GetBaseValue(),MaxHealth.GetCurrentValue());
		//if (TargetCharacter)
		//{
		//	// Call for all health changes
		//	TargetCharacter->HandleHealthChanged(DeltaValue, SourceTags);
		//}
	}
}


