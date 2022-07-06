#pragma once

class Utils
{
public:
	
	static void DebugMsg(const FString& Component,const FString& Msg)
	{
		GlobalNoticing(Component, Msg, FColor::Cyan);
	}
	
	static void GlobalNoticing(const FString& Component, const FString& Msg, const FColor Color)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, Color,TEXT("[" + Component + TEXT("-Alert] ") + Msg)); 
	}
};
