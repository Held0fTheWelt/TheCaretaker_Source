/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Widgets/EnumToString/EnumToStringUserWidget.h"

UEnumToStringUserWidget::UEnumToStringUserWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{

}

template<typename T>
FString UEnumToStringUserWidget::EnumToString(const FString& enumName, const T value, const FString& defaultValue) const
{
    UEnum* pEnum = FindObject<UEnum>(ANY_PACKAGE, *enumName, true);
    return pEnum
        ? UEnumToStringUserWidget::ExpandEnumString(pEnum->GetNameByIndex(static_cast<uint8>(value)).ToString(), enumName)
        : defaultValue;
}

FString UEnumToStringUserWidget::ExpandEnumString(const FString& name, const FString& enumName)
{
    FString expanded(name);
    FString spaceLetter("");
    FString spaceNumber("");
    FString search("");
    expanded.ReplaceInline(*enumName, TEXT(""), ESearchCase::CaseSensitive);
    expanded.ReplaceInline(TEXT("::"), TEXT(""), ESearchCase::CaseSensitive);
    for (TCHAR letter = 'A'; letter <= 'Z'; ++letter)
    {
        search = FString::Printf(TEXT("%c"), letter);
        spaceLetter = FString::Printf(TEXT(" %c"), letter);
        expanded.ReplaceInline(*search, *spaceLetter, ESearchCase::CaseSensitive);
    }
    for (TCHAR number = '0'; number <= '9'; ++number)
    {
        search = FString::Printf(TEXT("%c"), number);
        spaceNumber = FString::Printf(TEXT(" %c"), number);
        expanded.ReplaceInline(*search, *spaceNumber, ESearchCase::CaseSensitive);
    }
    expanded.ReplaceInline(TEXT("_"), TEXT(" -"), ESearchCase::CaseSensitive);
    expanded = expanded.RightChop(1).TrimStart().TrimEnd();
    return expanded;
}