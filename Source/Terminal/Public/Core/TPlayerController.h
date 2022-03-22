// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TERMINAL_API ATPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	/** Game Input Only, with custom boolean to prevent mouse consume */
	UFUNCTION(BlueprintCallable, BlueprintCosmetic, Category="Input")
	static void SetInputMode_GameOnly_MouseConsume(APlayerController* PlayerController, bool ConsumeCaptureMouseDown);
};
