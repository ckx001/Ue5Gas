// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AttributeSetBase.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FHealthDelegate, float, Health, float, MaxHealth);

UCLASS()
class GASPLUG_API UAttributeSetBase : public UAttributeSet
{
	GENERATED_BODY()
	
	UAttributeSetBase();
public:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Health and MaxHealth
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Abilities", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Health);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Abilities", ReplicatedUsing = OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, MaxHealth);

	UFUNCTION()
    virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Abilities", ReplicatedUsing = OnRep_Ack)
	FGameplayAttributeData Ack;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Ack);
	
	UFUNCTION()
	virtual void OnRep_Ack(const FGameplayAttributeData& OldAck);

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Abilities", ReplicatedUsing = OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAttributeSetBase, Armor);
	
	UFUNCTION()
	virtual void OnRep_Armor(const FGameplayAttributeData& OldArmor);
	
	UPROPERTY(BlueprintReadOnly, BlueprintAssignable)
	FHealthDelegate onHealthChangeDelegate;
	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
};
