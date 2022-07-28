// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "AbilitySystemComponent.h"
#include "UnrealWidgetFwd.h"
#include "Components/ProgressBar.h"

// Sets default values
ACharacterBase::ACharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	attributeComponent = CreateDefaultSubobject<UAttributeSetBase>(TEXT("attributeComponent"));
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystem"));
	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WidgetComponent"));
	Widget->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	if(AbilitySystemComponent != nullptr)
	{
		if(PreloadedAbilities.Num() > 0)
		{
			for(auto i =0;i < PreloadedAbilities.Num(); i++)
			{
				if(PreloadedAbilities[i] != nullptr)
				{
					AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(PreloadedAbilities[i].GetDefaultObject(),1,0));
				}
			}

		}

		AbilitySystemComponent->InitAbilityActorInfo(this,this);
	}

	//Init Widget
	auto InfoWidegetClass = LoadClass<UUserWidget>(NULL, TEXT("WidgetBlueprint'/Game/Characters/WBP_PlyaerStatus.WBP_PlyaerStatus_C'"));
	Widget->SetWidgetClass(InfoWidegetClass);
	Widget->SetWidgetSpace(EWidgetSpace::Screen);
	Widget->SetPivot(FVector2D(1, 0.5));
	Widget->SetDrawSize(FVector2D(120.0f, 10.0f));
	Widget->SetRelativeLocation(FVector(0.0f, 0.0f, 95.0f));
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ACharacterBase::RefreshHp(float Percent)
{
	UUserWidget* InfoWidget = Widget->GetUserWidgetObject();
	if (InfoWidget) {
		auto ProgressBar = Cast<UProgressBar>(InfoWidget->GetWidgetFromName(TEXT("PB_HP")));
		if (ProgressBar)
			ProgressBar->SetPercent(Percent);
	}
}