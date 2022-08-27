// Fill out your copyright notice in the Description page of Project Settings.


#include "LauchActor.h"
#include "AbilitySystemComponent.h"

// Sets default values
ALauchActor::ALauchActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	attributeComponent = CreateDefaultSubobject<UAttributeSetBase>(TEXT("attributeComponent"));
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
}

// Called when the game starts or when spawned
void ALauchActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALauchActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

