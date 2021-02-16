/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */


#include "Structs/Messages/CaretakerMessages.h"

FGameMessage::FGameMessage()
{
	MessageType = EGameMessageType::GMT_None;
	Message = FText::FromString("");
}
FGameMessage::FGameMessage(EGameMessageType Type)
{
	MessageType = Type;
	Message = FText::FromString("");
}
FGameMessage::FGameMessage(EGameMessageType Type, FText Msg)
{
	MessageType = Type;
	Message = Msg;
}

FCaretakerMessages::FCaretakerMessages()
{
	GameMessages.Empty();

	GameMessages.Add(FGameMessage(EGameMessageType::GMT_TITLE_PAUSE, FText::FromString(TEXT("Pause+"))));
	GameMessages.Add(FGameMessage(EGameMessageType::GMT_SUB_PAUSE, FText::FromString(TEXT(""))));
	GameMessages.Add(FGameMessage(EGameMessageType::GMT_TITLE_VICTORY, FText::FromString(TEXT("Victory!+"))));
	GameMessages.Add(FGameMessage(EGameMessageType::GMT_SUB_VICTORY, FText::FromString(TEXT("You have survived the night! Brace yourself for the next Part.+"))));
	GameMessages.Add(FGameMessage(EGameMessageType::GMT_TITLE_DEATH, FText::FromString(TEXT("Game Over+"))));
	GameMessages.Add(FGameMessage(EGameMessageType::GMT_SUB_DEATH_SPD, FText::FromString(TEXT("The dungeon spider is attacking you. You must repeat your night watch.+"))));
	GameMessages.Add(FGameMessage(EGameMessageType::GMT_SUB_DEATH_NSE, FText::FromString(TEXT("The jailer woke up. You were too loud. You must repeat your vigil.+"))));
	GameMessages.Add(FGameMessage(EGameMessageType::GMT_SUB_DEATH_TME, FText::FromString(TEXT("You were killed, because you triggered a trap in the dungeon.+"))));
	GameMessages.Add(FGameMessage(EGameMessageType::GMT_SUB_DEATH_TRP, FText::FromString(TEXT("The night is over. You failed to complete all of your tasks. You have to repeat your Nightwatch+"))));
}

FText FCaretakerMessages::GetTextForMessageType(EGameMessageType MessageType)
{
	for (auto GameMessage : GameMessages)
	{
		if (GameMessage.MessageType == MessageType)
		{
			return GameMessage.Message;
		}
	}

	return FText::FromString(TEXT("Message for Type not found !"));
}
