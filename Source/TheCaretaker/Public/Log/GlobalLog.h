/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#define GET_CLASSNAME_WITH_FUNCTION FString(__FUNCTION__)
#define GET_LINE_NUMBER FString::FromInt(__LINE__)

// Output of Log ->		GameClass::Function [16]: some stuff
#define LOG_DEFAULT(LogCategory, Message) UE_LOG(LogCategory, Log, TEXT("%s [%s]:	%s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_DISPLAY(LogCategory, Message) UE_LOG(LogCategory, Display, TEXT("%s [%s]:	%s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_VERBOSE(LogCategory, Message) UE_LOG(LogCategory, Verbose, TEXT("%s	[%s]:	%s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_VERY_VERBOSE(LogCategory, Message) UE_LOG(LogCategory, VeryVerbose, TEXT("%s [%s]:	%s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_WARNING(LogCategory, Message) UE_LOG(LogCategory, Warning, TEXT("%s [%s]:	%s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_ERROR(LogCategory, Message) UE_LOG(LogCategory, Error, TEXT("%s [%s]:	%s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))
#define LOG_FATAL(LogCategory, Message) UE_LOG(LogCategory, Fatal, TEXT("%s [%s]:	%s"), *GET_CLASSNAME_WITH_FUNCTION, *GET_LINE_NUMBER, *FString(Message))

#define HELP 	LOG_WARNING(RuntimeLog, "You forgot to code these lines ! Help !") ; LOG_DISPLAY(RuntimeLog, "You forgot to code these lines ! Help !")

DEFINE_LOG_CATEGORY_STATIC(InitializationLog, All, All)
DEFINE_LOG_CATEGORY_STATIC(KeyBindingLog, All, All)
DEFINE_LOG_CATEGORY_STATIC(AudioDebugLog, All, All)
DEFINE_LOG_CATEGORY_STATIC(RuntimeLog, All, All)
DEFINE_LOG_CATEGORY_STATIC(SettingsLog, All, All)
DEFINE_LOG_CATEGORY_STATIC(SaveGameLog, All, All)
DEFINE_LOG_CATEGORY_STATIC(RuntimeExecutionLog, All, All)
DEFINE_LOG_CATEGORY_STATIC(ShutdownLog, All, All)

#define DEBUG_MSG(x, ...) if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT(x), __VA_ARGS__));}
