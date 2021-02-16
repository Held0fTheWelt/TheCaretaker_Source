/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Widgets/BackButton/BackButtonUserWidget.h"
#include "ExtrasMenuUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UExtrasMenuUserWidget : public UBackButtonUserWidget
{
	GENERATED_BODY()
	
public:
	UExtrasMenuUserWidget(const FObjectInitializer& ObjectInitializer);

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* BackgroundButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* PreviousLevel;

	UPROPERTY(meta = (BindWidget))
	class UButton* NextLevel;

	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* SolvedSecrets;

	/// Dungeon 1 Part 1 

	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_1_0;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_1_1;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_1_2;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_1_3;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_1_4;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_1_5;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_1_6;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_1_7;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_1_8;

	/// Dungeon 1 Part 2
	
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_2_0;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_2_1;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_2_2;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_2_3;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_2_4;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_2_5;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_2_6;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_2_7;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_2_8;

	/// Dungeon 1 Part 3

	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_3_0;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_3_1;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_3_2;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_3_3;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_3_4;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_3_5;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_3_6;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_3_7;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_3_8;

	/// Dungeon 2 Part 1 

	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_4_0;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_4_1;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_4_2;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_4_3;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_4_4;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_4_5;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_4_6;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_4_7;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_4_8;

	/// Dungeon 2 Part 2

	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_5_0;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_5_1;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_5_2;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_5_3;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_5_4;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_5_5;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_5_6;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_5_7;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_5_8;

	/// Dungeon 2 Part 3

	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_6_0;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_6_1;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_6_2;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_6_3;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_6_4;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_6_5;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_6_6;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_6_7;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_6_8;

	/// Dungeon 3 Part 1 

	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_7_0;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_7_1;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_7_2;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_7_3;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_7_4;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_7_5;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_7_6;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_7_7;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_7_8;

	/// Dungeon 3 Part 2

	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_8_0;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_8_1;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_8_2;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_8_3;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_8_4;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_8_5;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_8_6;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_8_7;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_8_8;

	/// Dungeon 3 Part 3

	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_9_0;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_9_1;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_9_2;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_9_3;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_9_4;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_9_5;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_9_6;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_9_7;
	UPROPERTY(meta = (BindWidget))
	class USecretCredentialsItemUserWidget* Credentials_9_8;

public:
	virtual void ShowParent() override;

protected:
	virtual void NativeConstruct() override;

	virtual void ReturnToParent() override;

	virtual void ClearAllData();

	void AddCredentialsToArray();
	
	UFUNCTION(BlueprintCallable)
	virtual void UpdateTableData();
private:
	UFUNCTION()
	void ShowNextLevel();
	UFUNCTION()
	void ShowPreviousLevel();

	UPROPERTY()
	TArray<class USecretCredentialsItemUserWidget*> AllCredentials;

	UPROPERTY()
	int32 CurrentLevel;
	UPROPERTY()
	int32 Count;

	UPROPERTY()
	TArray<class UTextBlock*> SecretSlogans;
};
