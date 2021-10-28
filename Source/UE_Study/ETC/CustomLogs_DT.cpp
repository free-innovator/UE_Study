// Fill out your copyright notice in the Description page of Project Settings.

#if WITH_EDITOR
#include "CustomLogs_DT.h"


DEFINE_LOG_CATEGORY(AoAIR);

#define FatalLog(format, ...) UE_LOG(AoAIR, Fatal, TEXT(format), ##__VA_ARGS__)
#define ErrorLog(format, ...) UE_LOG(AoAIR, Error, TEXT(format), ##__VA_ARGS__)
#define WarningLog(format, ...) UE_LOG(AoAIR, Warning, TEXT(format), ##__VA_ARGS__)
#define DisplayLog(format, ...) UE_LOG(AoAIR, Display, TEXT(format), ##__VA_ARGS__)
#define Log(format, ...) UE_LOG(AoAIR, Log, TEXT(format), ##__VA_ARGS__)


//CustomLogs::CustomLogs()
//{
//}

//CustomLogs::~CustomLogs()
//{
//	if (!bShowMessage || Message.IsEmpty())
//	{
//		return;
//	}
//
//	switch (LogType)
//	{
//	case 0:
//		if (GEngine)
//		{
//			GEngine->AddOnScreenDebugMessage(Count, Time, Color, Message);
//		}
//		break;
//	case 1:
//		UE_LOG(LogTemp, Log, TEXT("%s"), *Message)
//			break;
//	case 2:
//		UE_LOG(LogTemp, Warning, TEXT("%s"), *Message)
//			break;
//	case 3:
//		UE_LOG(LogTemp, Error, TEXT("%s"), *Message)
//			break;
//	}
//}


#endif