// Fill out your copyright notice in the Description page of Project Settings.


#include "BouncePad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "BouncePadDemoCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABouncePad::ABouncePad()
{
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(RootComponent);

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABouncePad::HandleOverlap);
}

void ABouncePad::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABouncePadDemoCharacter* Character = Cast<ABouncePadDemoCharacter>(OtherActor);
	if (Character == nullptr)
	{
		return;
	}

	Character->LaunchCharacter(Force * GetActorUpVector(), true, true);
}