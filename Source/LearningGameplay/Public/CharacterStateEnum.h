#pragma once

UENUM(BlueprintType)
enum class ECharacterState : uint8 {
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_equippedWeapon UMETA(DisplayName = "equippedWeapon"),
	ECS_equippedTHWeapon UMETA(DisplayName = "equippedTHWeapon")
};

UENUM(BlueprintType)
enum class EActionState : uint8 {
	ECS_Unoccupied UMETA(DisplayName = "Unoccupied"),
	ECS_Attacking UMETA(DisplayName = "Attacking"),
};