// Fill out your copyright notice in the Description page of Project Settings.


#include "CustomCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ACustomCharacter::ACustomCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ACustomCharacter::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ACustomCharacter::ActorEndOverlap);
}

// Called every frame
void ACustomCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(isClimbing && wallActor != nullptr) {

		float rotation = wallActor->GetActorRotation().GetComponentForAxis(EAxis::Z);
		FRotator rotator = GetActorRotation();
		rotator.SetComponentForAxis(EAxis::Z, rotation);
		SetActorRotation(rotator);
	}
}

// Called to bind functionality to input
void ACustomCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ACustomCharacter::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Climb")) {
		GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Flying);
		GetCharacterMovement()->SetJumpAllowed(false);
		isClimbing = true;
		wallActor = OtherActor;
		//GetCharacterMovement()->MaxFlySpeed = ClimbMaxSpeed;
		JumpCurrentCount = 0;
	}
}

void ACustomCharacter::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Climb")) {
		FHitResult hit;
		FVector start = GetActorLocation();
		if(GetWorld()->LineTraceSingleByChannel(hit,start,start+GetActorUpVector()*-2000,ECC_Visibility))
			GetCharacterMovement()->SetMovementMode(EMovementMode::MOVE_Walking);
		DrawDebugLine(GetWorld(), start, start + GetActorUpVector() * -2000, FColor::Red);
		GetCharacterMovement()->SetJumpAllowed(true);
		isClimbing = false;
		wallActor = nullptr;
		//GetCharacterMovement()->MaxFlySpeed = WalkMaxSpeed;
	}
}
