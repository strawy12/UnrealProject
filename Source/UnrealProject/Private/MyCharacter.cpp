// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Log, TEXT("Sss2SSdasddaS"));
	
}

// Called every frame
void AMyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    MoveForward();
}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyCharacter::MoveForward()
{
    FVector MoveDirection = GetActorForwardVector();
    FVector MoveVelocity = MoveDirection * moveSpeed * GetWorld()->GetDeltaSeconds();
    FVector NewLocation = GetActorLocation() + MoveVelocity;

    SetActorLocation(NewLocation);

}

void AMyCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

    // 충돌된 다른 액터의 이름을 가져옵니다.
    FString OtherActorName = Other->GetName();

    // 로그를 출력합니다.
    UE_LOG(LogTemp, Log, TEXT("SSSdasddaS"));
}


