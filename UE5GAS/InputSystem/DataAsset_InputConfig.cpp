#include "DataAssets/Input/DataAsset_InputConfig.h"
#include "RoxyDebugHelper.h"

UInputAction* UDataAsset_InputConfig::FindNativeInputActionByTag(const FGameplayTag& InInputTag) const
{
	for (const FInputActionConfig& InputActionConfig : NativeInputActions)
	{
		if (InputActionConfig.InputTag == InInputTag && InputActionConfig.InputAction)
		{
			return InputActionConfig.InputAction;
		}
	}

	Debug::LogError(FString::Printf(TEXT("InputAction not found for tag: %s"), *InInputTag.ToString()));
	return nullptr;
}