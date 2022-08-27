#include "GE_Calculation.h"
#include "AttributeSetBase.h"


struct GDDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(Ack);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	DECLARE_ATTRIBUTE_CAPTUREDEF(Damage);
	
	GDDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Ack, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Damage, Source, true);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAttributeSetBase, Armor, Target, true);
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
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	RelevantAttributesToCapture.Add(DamageStatics().DamageDef);
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


	float AckPercent = Spec.GetSetByCallerMagnitude(FGameplayTag::RequestGameplayTag(FName("AckPercent")), false, -1.0f);
	AckPercent = FMath::Max<float>(AckPercent, 0.0f);
	//UE_LOG(LogTemp,Warning,TEXT("BBBBBBBBBBB=%f"),AckPercent);
	
	///
	float Ack = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().AckDef, EvaluationParameters, Ack);
	//UE_LOG(LogTemp,Warning,TEXT("CCCCCCCCC=%f"),Ack);
	float Armor = 0.0f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, Armor);
	Armor = FMath::Max<float>(Armor, 0.0f);
	
	float DamageDone = Ack * AckPercent - Armor;
	//UE_LOG(LogTemp,Warning,TEXT("DDDDDDDDDDD=%f"),Armor);
	if(DamageDone > 0.f)
	{
		//UE_LOG(LogTemp,Warning,TEXT("EEEEEEEEEEE=%f"),DamageDone);
	    OutExecutionOutput.AddOutputModifier(FGameplayModifierEvaluatedData(DamageStatics().DamageProperty, EGameplayModOp::Additive, DamageDone));
	}
}
