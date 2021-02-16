/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "SecretCredentialsItemUserWidget.h"

#include "Log/GlobalLog.h"

#include "Widgets/Secret/SecretCredentialUserWidget.h"

void USecretCredentialsItemUserWidget::SetCredentialInfos(int32 CredentialIndex, FString Character, FLinearColor TextColorCode, FLinearColor OutlineColorCode, int32 ConnectedSloganIndex, TArray<int32> SolvedSloganIndices)
{
	if (CredentialIndex == -1)
	{
		SetVisibility(ESlateVisibility::Hidden);
		Credential1->SetCredentialInformation("", FLinearColor::Transparent, FLinearColor::Transparent);
		Credential2->SetCredentialInformation("", FLinearColor::Transparent, FLinearColor::Transparent);
		return;
	}

	if (Character == "")
	{
		SetVisibility(ESlateVisibility::Hidden);
		if (CredentialIndex == 0)
		{
			Credential1->SetCredentialInformation("", FLinearColor::Transparent, FLinearColor::Transparent);
		}
		else if (CredentialIndex == 1)
		{
			Credential2->SetCredentialInformation("", FLinearColor::Transparent, FLinearColor::Transparent);
		}
		return;
	}

	if (CredentialIndex == 0)
	{
		Credential1->SetCredentialInformation(Character, TextColorCode, OutlineColorCode);
		ConnectedSloganIndex1 = ConnectedSloganIndex;
	}
	else if (CredentialIndex == 1)
	{
		Credential2->SetCredentialInformation(Character, TextColorCode, OutlineColorCode);
		ConnectedSloganIndex2 = ConnectedSloganIndex;
	}
	else
	{
		LOG_WARNING(RuntimeExecutionLog, "Index too high ! This shouldn't happen !")
	}

	SetVisibility(ESlateVisibility::SelfHitTestInvisible);

	Credential1->SetIsEnabled(true);
	Credential2->SetIsEnabled(true);

	for (int32 i = 0; i < SolvedSloganIndices.Num(); i++)
	{
		CheckForSolvedSloganIndex(SolvedSloganIndices[i]);
	}
}

void USecretCredentialsItemUserWidget::CheckForSolvedSloganIndex(int32 SolvedSloganIndex)
{
	if (SolvedSloganIndex == ConnectedSloganIndex1)
	{
		Credential1->SetIsEnabled(false);
	}
	if (SolvedSloganIndex == ConnectedSloganIndex2)
	{
		Credential2->SetIsEnabled(false);
	}
}
