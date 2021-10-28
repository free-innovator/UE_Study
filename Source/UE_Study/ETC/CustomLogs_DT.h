// Fill out your copyright notice in the Description page of Project Settings.
#if WITH_EDITOR
#pragma once

//#include "CoreMinimal.h"
#include "Engine/Engine.h"

DECLARE_LOG_CATEGORY_EXTERN(AoAIR, Log, All);

/**
 * 
 */
class CustomLogs
{
public:
//	CustomLogs();
//	~CustomLogs();

public:
	//	一键控制信息的显示
	bool bShowMessage = true;

private:
	//	Screen	
	int32 Count;	//	行数
	float Time;		//	时长
	FColor Color;	//	颜色
	FString Message;//	信息

	//	log
	uint8 LogType;	//	类型

public:
	//	析构函数
	~CustomLogs()
	{
		if (!bShowMessage || Message.IsEmpty())
		{
			return;
		}

		switch (LogType)
		{
		case 0:
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(Count, Time, Color, Message);
			}
			break;
		case 1:
			UE_LOG(AoAIR, Warning, TEXT("%s"), *Message)
				break;
		case 2:
			UE_LOG(AoAIR, Fatal, TEXT("%s"), *Message)
				break;
		case 3:
			UE_LOG(AoAIR, Error, TEXT("%s"), *Message)
				break;
		case 4:
			UE_LOG(AoAIR, Warning, TEXT("%s"), *Message)
				break;
		case 5:
			UE_LOG(AoAIR, Display, TEXT("%s"), *Message)
				break;
		case 6:
			UE_LOG(AoAIR, Log, TEXT("%s"), *Message)
				break;
		}
	}

	//	初始化
	void InitScreen(int32 ShowCount, float ShowTime, FColor ShowColor)
	{
		this->LogType = 0;
		this->Count = ShowCount;
		this->Time = ShowTime;
		this->Color = ShowColor;
	}
	void InitLog(int32 Type)
	{
		this->LogType = Type;
	}

	//	操作符重写
	CustomLogs& operator+ (int32 Info) { Message.Append(FString::FromInt(Info)); return *this; }
	CustomLogs& operator+ (float Info) { Message.Append(FString::SanitizeFloat(Info)); return *this; }
	CustomLogs& operator+ (double Info) { Message.Append(FString::SanitizeFloat(Info)); return *this; }
	CustomLogs& operator+ (bool Info) { Message.Append(Info ? FString("true") : FString("false")); return *this; }
	CustomLogs& operator+ (const wchar_t* Info) { Message += Info; return *this; }
	CustomLogs& operator+ (const char* Info) { Message += UTF8_TO_TCHAR(Info); return *this; }
	CustomLogs& operator+ (const char Info) { Message.AppendChar(Info); return *this; }
	CustomLogs& operator+ (FString Info) { Message.Append(Info); return *this; };
	CustomLogs& operator+ (FName Info) { Message.Append(Info.ToString()); return *this; }
	CustomLogs& operator+ (FText Info) { Message.Append(Info.ToString()); return *this; }
	CustomLogs& operator+ (FVector2D Info) { Message.Append(Info.ToString()); return *this; }
	CustomLogs& operator+ (FVector Info) { Message.Append(Info.ToString()); return *this; }
	CustomLogs& operator+ (FRotator Info) { Message.Append(Info.ToString()); return *this; }
	CustomLogs& operator+ (FQuat Info) { Message.Append(Info.ToString()); return *this; }
	CustomLogs& operator+ (FTransform Info) { Message.Append(Info.ToString()); return *this; }
	CustomLogs& operator+ (FMatrix Info) { Message.Append(Info.ToString()); return *this; }
	CustomLogs& operator+ (FColor Info) { Message.Append(Info.ToString()); return *this; }
	CustomLogs& operator+ (FLinearColor Info) { Message.Append(Info.ToString()); return *this; }

};

//	Screen
FORCEINLINE CustomLogs Print()
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitScreen(-1, 9999, FColor::Green);
	return PrintHelper;
}
FORCEINLINE CustomLogs Print(int Count)
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitScreen(Count, 9999, FColor::Green);
	return PrintHelper;
}
FORCEINLINE CustomLogs Print(float Time)
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitScreen(-1, Time, FColor::Green);
	return PrintHelper;
}
FORCEINLINE CustomLogs Print(FColor Color)
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitScreen(-1, 9999, Color);
	return PrintHelper;
}
FORCEINLINE CustomLogs Print(int Count, float Time)
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitScreen(Count, Time, FColor::Green);
	return PrintHelper;
}
FORCEINLINE CustomLogs Print(int Count, FColor Color)
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitScreen(Count, 9999, Color);
	return PrintHelper;
}
FORCEINLINE CustomLogs Print(float Time, FColor Color)
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitScreen(-1, Time, Color);
	return PrintHelper;
}
FORCEINLINE CustomLogs Print(int Count, float Time, FColor Color)
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitScreen(Count, Time, Color);
	return PrintHelper;
}


//	枚举转换
template<typename TEnum>
FORCEINLINE FString EnumToString(TEnum EnumValue, FString EnumTypeName)
{
	UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, *EnumTypeName, true);

	if (!EnumPtr)
	{
		return FString("InvaildEnumName");
	}

	return EnumPtr->GetNameStringByIndex((int32)EnumValue);
}

template<typename TEnum>
FORCEINLINE FName EnumToName(TEnum EnumValue, FString EnumTypeName)
{
	UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, *EnumTypeName, true);

	if (!EnumPtr)
	{
		return FName("InvaildEnumName");
	}

	return EnumPtr->GetEnumName((int32)EnumValue);
}

template<typename TEnum>
FORCEINLINE TEnum NameToEnum(FString EnumTypeName, FName EnumValue)
{
	UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, *EnumTypeName, true);

	if (!EnumPtr)
	{
		return TEnum(0);
	}

	return (TEnum)EnumPtr->GetIndexByName(EnumValue);
}

template<typename TEnum>
FORCEINLINE int32 NameToIndex(FString EnumTypeName, FName EnumValue)
{
	UEnum* EnumPtr = FindObject<UEnum>((UObject*)ANY_PACKAGE, *EnumTypeName, true);

	if (!EnumPtr)
	{
		return -1;
	}

	return EnumPtr->GetIndexByName(EnumValue);
}

//	log
FORCEINLINE CustomLogs Log()
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitLog(1);
	return PrintHelper;
}
FORCEINLINE CustomLogs FatalLog()
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitLog(2);
	return PrintHelper;
}
FORCEINLINE CustomLogs ErrorLog()
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitLog(3);
	return PrintHelper;
}
FORCEINLINE CustomLogs WarningLog()
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitLog(4);
	return PrintHelper;
}
FORCEINLINE CustomLogs DisplayLog()
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitLog(5);
	return PrintHelper;
}
FORCEINLINE CustomLogs NormalLog()
{
	CustomLogs PrintHelper = CustomLogs();
	PrintHelper.InitLog(6);
	return PrintHelper;
}




#endif