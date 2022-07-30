#include "GE_Calculation.h"
#include "AttributeSetBase.h"


struct GDDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Ack);

	GDDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Ack, Source, true);
		
	}
};

static const GDDamageStatics& DamageStatics()
{
	static GDDamageStatics DStatics;
	return DStatics;
}

UGE_Calculation::UGE_Calculation()
{
	RelevantAttributesToCapture.Add(DamageStatics().AckDef);
}

void UGE_Calculation::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	//OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageProperty, EGameplayModOp::Additive, MitigatedDamage));
	UAbilitySystemComponent* TargetAbilitySystemComponent = ExecutionParams.GetTargetAbilitySystemComponent();
	UAbilitySystemComponent* SourceAbilitySystemComponent = ExecutionParams.GetSourceAbilitySystemComponent();

	AActor* SourceActor = SourceAbilitySystemComponent ? SourceAbilitySystemComponent->GetAvatarActor() : nullptr;
	AActor* TargetActor = TargetAbilitySystemComponent ? TargetAbilitySystemComponent->GetAvatarActor() : nullptr;
	UGE_Calculation* TargetASC = Cast<UGE_Calculation>(TargetAbilitySystemComponent);
	if (TargetASC)
	{
		UGE_Calculation* SourceASC = Cast<UGE_Calculation>(SourceAbilitySystemComponent);
		//TargetASC->ReceiveDamage(SourceASC, 1, 1);
	}
	
	const FGameplayEffectSpec& Spec = ExecutionParams.GetOwningSpec();

	// Gather the tags from the source and target as that can affect which buffs should be used
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;
	
	float Damage = 10.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AckDef, EvaluationParameters, Damage);

	float DamageDone = 10.0f;
	OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().AckProperty, EGameplayModOp::Additive, DamageDone));
}
