/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "SecretCredentialUserWidget.h"
#include "Components/TextBlock.h"
#include "Containers/UnrealString.h"
#include "Containers/StringConv.h"

void USecretCredentialUserWidget::SetCredentialInformation(FString CredentialLetter, FLinearColor TextColor, FLinearColor OutlineColor)
{
	
	if (CredentialLetter.Len() > 1)
	{
		CredentialLetter = CredentialLetter.LeftChop(2);
	}
	PerformCredentialInformation(CredentialLetter, TextColor, OutlineColor);
}

void USecretCredentialUserWidget::PerformCredentialInformation(FString CredentialLetter, FLinearColor TextColor, FLinearColor OutlineColor)
{
	// Set Credential
	Credential->SetText(FText::FromString(CredentialLetter));
	
	//UE_LOG(LogTemp, Warning, TEXT("Color %f, %f, %f, %f"), TextColor.R, TextColor.G, TextColor.B, TextColor.A);

	// Set Credential Color
	
	

	Credential->SetColorAndOpacity(TextColor);

	// Set Outlining Color
	FSlateFontInfo& FontInfo = Credential->Font;
	FontInfo.OutlineSettings.OutlineColor = OutlineColor;
}
