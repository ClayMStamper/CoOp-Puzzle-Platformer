// Fill out your copyright notice in the Description page of Project Settings.


#include "ButtonPlatform.h"

#include "Components/BoxComponent.h"

// Sets default values
AButtonPlatform::AButtonPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Setup trigger volume
	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	check(TriggerVolume)
	RootComponent = TriggerVolume;
	
}

// Called when the game starts or when spawned
void AButtonPlatform::BeginPlay()
{
	Super::BeginPlay();
	TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AButtonPlatform::OnOverlapBegin);
	TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AButtonPlatform::OnOverlapEnd);
}

// Called every frame
void AButtonPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AButtonPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	UE_LOG(LogTemp, Warning, TEXT("Activated!"));
	
	if (PlatformToActivateObjectRef)
	{
		Cast<IButtonActivatable>(PlatformToActivateObjectRef)->Activate(this);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Platform to activate's UObject* is NULL"));
	}

}

void AButtonPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Deactivated!"));
}



