// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSetBase.h"
#include "GameFramework/Actor.h"
#include "LauchActor.generated.h"

UCLASS()
class UE5GAS_API ALauchActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALauchActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category = "Properties")
	class UAttributeSetBase* attributeComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Character Abilities")
	class UAbilitySystemComponent* AbilitySystemComponent;
};
