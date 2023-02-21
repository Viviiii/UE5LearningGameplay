#pragma once

UENUM(BlueprintType)
enum class EWeaponState : uint8 {
	EWS_Pickable UMETA(DisplayName = "Pickable"),
	EWS_Equipped UMETA(DisplayName = "equipped"),
};