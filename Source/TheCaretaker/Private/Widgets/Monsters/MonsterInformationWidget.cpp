/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "MonsterInformationWidget.h"

#include "Widgets/Monsters/HungerBar/MonsterHungerBarWidget.h"
#include "Components/TextBlock.h"


void UMonsterInformationWidget::SetMonsterImage(UTexture2D* Image)
{
	MonsterHunger->SetMonsterImage(Image);
}

void UMonsterInformationWidget::SetProgressBarPercentage(float Value)
{
	MonsterHunger->SetProgressBarPercentage(Value);
}

void UMonsterInformationWidget::SetMonsterName(FText Name)
{
	MonsterName->SetText(Name);
}

