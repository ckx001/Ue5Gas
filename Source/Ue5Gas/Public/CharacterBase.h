// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CharacterBase.generated.h"

UCLASS()
class UE5GAS_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	////////////////////////
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Character Abilities")
	class UAbilitySystemComponent* AbilitySystemComponent;
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Character Abilities")
	TArray<TSubclassOf<class UGameplayAbility>> PreloadedAbilities;
	////////////////////////
	///
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const;
};
