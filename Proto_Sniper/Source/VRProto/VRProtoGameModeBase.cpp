// Fill out your copyright notice in the Description page of Project Settings.

#include "VRProtoGameModeBase.h"
#include "UObject/ConstructorHelpers.h"

AVRProtoGameModeBase::AVRProtoGameModeBase()
	: Super()
{
	// Set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Characters/Player/BP_PawnVR"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/Characters/Player/BP_PawnVR_Weapons"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
}


