#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8 {
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_equippedWeapon UMETA(DisplayName = "equippedWeapon"),
	ECS_equippedTHWeapon UMETA(DisplayName = "equippedTHWeapon")
};

UENUM(BlueprintType)
enum class EActionState : uint8 {
	EAS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	EAS_Attacking UMETA(DisplayName = "Attacking"),
};

UENUM(BlueprintType)
enum class EDeathState : uint8 {
	ECS_Alive UMETA(DisplayName = "Alive"),
	ECS_Dead UMETA(DisplayName = "Dead"),
	ECS_Dead1 UMETA(DisplayName = "Dead1"),
	ECS_Dead2 UMETA(DisplayName = "Dead2"),
	ECS_Dead3 UMETA(DisplayName = "Dead3"),
};