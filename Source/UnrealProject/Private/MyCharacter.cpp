// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "C:/Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "C:/Program Files/Epic Games/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include <math.h>

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	if (springArmComp)
	{
		springArmComp->SetupAttachment(RootComponent);
		springArmComp->SetRelativeLocation(FVector(0, 70, 90));
		springArmComp->TargetArmLength = 400;
	}

	// 카메라 컴포넌트
	myCamComp = CreateDefaultSubobject<UCameraComponent>(TEXT("MyCamComp"));
	if (myCamComp)
	{
		myCamComp->SetupAttachment(springArmComp);
	}

}


// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
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

	APlayerController* PlayerController = Cast<APlayerController>(Controller);

	if (PlayerController)
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if (Subsystem)
		{
			Subsystem->AddMappingContext(myMappingContext, 0);
		}
	}

	UEnhancedInputComponent* EnhancedInputComp = CastChecked<UEnhancedInputComponent>(PlayerInputComponent);
	EnhancedInputComp->BindAction(moveRightAction, ETriggerEvent::Triggered, this, &AMyCharacter::MoveRight);
	EnhancedInputComp->BindAction(turnAction, ETriggerEvent::Triggered, this, &AMyCharacter::Turn);
}

void AMyCharacter::MoveForward()
{
	FVector MoveDirection = GetActorForwardVector();
	FVector MoveVelocity = MoveDirection * moveSpeed * GetWorld()->GetDeltaSeconds();
	FVector NewLocation = GetActorLocation() + MoveVelocity;

	SetActorLocation(NewLocation);
}


void AMyCharacter::MoveRight(const FInputActionValue& Value)
{
	float Movement = Value.Get<float>();

	if (abs(posX + (int)Movement) > 1)
		return;

	if (Controller != nullptr)
	{
		FVector MoveDirection = GetActorRightVector();
		this->posX += (int)Movement;

		FVector MoveVelocity = MoveDirection * Movement * rightSpeed;
		FVector NewLocation = GetActorLocation() + MoveVelocity;
		SetActorLocation(NewLocation);
	}
}

void AMyCharacter::Turn(const FInputActionValue& Value)
{
	float Movement = Value.Get<float>();

	if (Controller != nullptr)
	{
		return;
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw = Movement * 90.f;
		UE_LOG(LogTemp, Log, TEXT("%f"), GetActorRotation().Yaw);
		SetActorRotation(NewRotation);
		UE_LOG(LogTemp, Log, TEXT("%f"), GetActorRotation().Yaw);

	}
}

void AMyCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// 충돌된 다른 액터의 이름을 가져옵니다.
	FString OtherActorName = Other->GetName();

	// 로그를 출력합니다.

	FVector Direction = GetActorLocation() * -1.f * FVector::UpVector;
	Direction.Normalize();
	GetCharacterMovement()->AddImpulse(Direction * 100.f);
}


