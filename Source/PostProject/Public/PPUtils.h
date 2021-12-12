#pragma once

class PPUtils
{
public:
	template<typename T>
	static T* GetPPPlayerComponent(AActor* PlayerPawn)
	{
		if(!PlayerPawn) return nullptr;

		const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
		return  Cast<T>(Component);
	}
};