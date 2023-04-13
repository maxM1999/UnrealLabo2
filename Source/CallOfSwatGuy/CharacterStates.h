#pragma once

UENUM(BlueprintType)
enum class ECrouchState : uint8 
{
	ECS_Crouched UMETA(DisplayName="Crouched"),
	ECS_UnCrouched UMETA(DisplayName-"UnCrouched")
};
