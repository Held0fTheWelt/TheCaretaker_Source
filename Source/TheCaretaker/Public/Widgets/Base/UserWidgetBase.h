/* Copyright (C) 2020 Yves Tanas - All Rights Reserved */

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interfaces/Widgets/Base/UserWidgetBaseInterface.h"
#include "Interfaces/Widgets/SwitchToParent/SwitchableWidgetInterface.h"
#include "UserWidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class THECARETAKER_API UUserWidgetBase : public UUserWidget, public ISwitchableWidgetInterface, public IUserWidgetBaseInterface
{
	GENERATED_BODY()
	
public:
	// Geerbt über ISwitchableWidgetInterface
	virtual void ShowWidget(bool Show) override;
	virtual void SetParent(ISwitchableWidgetInterface* CurrentParent) override;
	UFUNCTION(BlueprintCallable, Category = "Parent" )
	virtual void ReturnToParent() override;
	virtual void ShowParent();
protected:
	virtual void NativeConstruct() override;

protected:
	bool bShow;

	ISwitchableWidgetInterface* Parent;

	class IGameInstanceAccessoryInterface* GameInstanceAccessor;
	class IGameInstanceMenuInterface* GameInstanceRouter;
	class IGameInstanceUIInterface* GameInstanceUI;

};
