// Copyright Epic Games, Inc. All Rights Reserved.

#include "DesignGateCharacter.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

//////////////////////////////////////////////////////////////////////////
// ADesignGateCharacter

void ADesignGateCharacter::ActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Climb")) {
		GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Flying;
		GetCharacterMovement()->SetJumpAllowed(false);
		IsClimbing = true;
		WallActor = OtherActor;
		GetCharacterMovement()->MaxFlySpeed = ClimbMaxSpeed;
		JumpCurrentCount = 0;
	}
}

void ADesignGateCharacter::ActorEndOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (OtherActor->ActorHasTag("Climb")) {
		GetCharacterMovement()->MovementMode = EMovementMode::MOVE_Walking;
		GetCharacterMovement()->SetJumpAllowed(true);
		IsClimbing = false;
		WallActor = nullptr;
		GetCharacterMovement()->MaxFlySpeed = WalkMaxSpeed;
	}
}

ADesignGateCharacter::ADesignGateCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

void ADesignGateCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (IsClimbing && WallActor != nullptr) {

		float rotation = WallActor->GetActorRotation().GetComponentForAxis(EAxis::Z);
		FRotator rotator = GetActorRotation();
		rotator.SetComponentForAxis(EAxis::Z, rotation);
		SetActorRotation(rotator);
	}
}

void ADesignGateCharacter::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &ADesignGateCharacter::ActorBeginOverlap);
	OnActorEndOverlap.AddDynamic(this, &ADesignGateCharacter::ActorEndOverlap);
	GetCharacterMovement()->MaxWalkSpeed = WalkMaxSpeed;
}

//////////////////////////////////////////////////////////////////////////
// Input

void ADesignGateCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAxis("MoveForward", this, &ADesignGateCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ADesignGateCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ADesignGateCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ADesignGateCharacter::LookUpAtRate);

	// handle touch devices
	PlayerInputComponent->BindTouch(IE_Pressed, this, &ADesignGateCharacter::TouchStarted);
	PlayerInputComponent->BindTouch(IE_Released, this, &ADesignGateCharacter::TouchStopped);

	// VR headset functionality
	PlayerInputComponent->BindAction("ResetVR", IE_Pressed, this, &ADesignGateCharacter::OnResetVR);
}


void ADesignGateCharacter::OnResetVR()
{
	// If DesignGate is added to a project via 'Add Feature' in the Unreal Editor the dependency on HeadMountedDisplay in DesignGate.Build.cs is not automatically propagated
	// and a linker error will result.
	// You will need to either:
	//		Add "HeadMountedDisplay" to [YourProject].Build.cs PublicDependencyModuleNames in order to build successfully (appropriate if supporting VR).
	// or:
	//		Comment or delete the call to ResetOrientationAndPosition below (appropriate if not supporting VR)
	UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
}

void ADesignGateCharacter::TouchStarted(ETouchIndex::Type FingerIndex, FVector Location)
{
		Jump();
}

void ADesignGateCharacter::TouchStopped(ETouchIndex::Type FingerIndex, FVector Location)
{
		StopJumping();
}

void ADesignGateCharacter::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ADesignGateCharacter::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ADesignGateCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		if (IsClimbing)
		{
			AddMovementInput(GetActorForwardVector(), Value > 0 ? Value / 10 : Value / 100);
			AddMovementInput(GetActorUpVector(), Value);
		}
		else {
			// find out which way is forward
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value);
		}
	}
}

void ADesignGateCharacter::MoveRight(float Value)
{
	if ( (Controller != nullptr) && (Value != 0.0f) )
	{
		if (IsClimbing) {
			AddMovementInput(GetActorForwardVector(), 0.1);
			AddMovementInput(GetActorRightVector(), Value);
		}
		else {
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value);
		}
	}
}

void ADesignGateCharacter::RunOn()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintMaxSpeed;
}

void ADesignGateCharacter::RunOff()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkMaxSpeed;
}
