#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "ParametersSave.generated.h"

UENUM(BlueprintType)
enum class ShieldModes : uint8
{
	STOP,
	DESTROY,
	SENDBACK,
	DEVIATION
};

UENUM(BlueprintType)
enum class ShockWaveModes : uint8
{
	STOP,
	DESTROY,
	PUSH
};

UENUM(BlueprintType)
enum class GetPowerOptions : uint8
{
	TRIGGER,
	BUFFER,
	DASH,
	COMBO
};

UENUM(BlueprintType)
enum class UsePowerOptions : uint8
{
	UNIQUE,
	INFINITE,
	INSTANT
};

UENUM(BlueprintType)
enum class LosePowerOptions : uint8
{
	TRIGGER,
	BUFFER,
	COOLDOWN
};

UCLASS()
class DESIGNGATE_API UParametersSave : public USaveGame
{
	GENERATED_BODY()

public:

	UParametersSave();
	
	// SPEAR
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SpearPower;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SpearGravity;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SpearComeBackDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SpearCooldown;

	// SHIELD
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShieldCooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShieldDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int ShieldLives;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ShieldModes ShieldMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShieldSendBackPower;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShieldDeviationPower;

	// SHOCKWAVE

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShockWaveCooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShockWaveSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShockWaveRange;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	ShockWaveModes ShockWaveMode;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ShockWavePushPower;

	// THROW

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float ThrowForce;

	// DASH

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanDash;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DashDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DashDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DashCooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DashInertiaForce;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float DashInertiaDuration;

	// GLIDE

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanGlide;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float GlideGravityScale;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float GlideMaxSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float GlideForwardSpeedMultiplier;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float GlideAirControl;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float GlideRotationSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool GlideLockCameraRotation;

	// SQUALL

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool CanSquall;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SquallDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SquallDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SquallPower;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SquallCooldown;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SquallOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SquallColliderScaleX;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SquallColliderScaleY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SquallColliderScaleZ;

	// WALL & CUBE

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float WallWidth;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float WallRiseDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float WallDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float WallRiseDelay;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float WallThickness;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool IsAimed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float WallOffset;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float WallMaxRange;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CubeScaleX;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CubeScaleY;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float CubeScaleZ;

	// POWERS

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	GetPowerOptions GetPowerOption;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UsePowerOptions UsePowerOption;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	LosePowerOptions LosePowerOption;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	bool PowerUseWithCombo;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float LosePowerCooldown;

	// MOVEMENTS

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Gravity;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float AirControl;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float RotationSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float WalkJumpVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float RunJumpVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SprintJumpVelocity;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float RunSpeed;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SprintSpeed;

	//SLOW MO

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SlowDuration;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float SlowRatio;
};
