// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StructEnumBPExample.generated.h"

UENUM(BlueprintType)
enum class EnumTest : uint8
{
	//GENERATED_BODY()

	ON UMETA(DisplayName = "On"),
	OFF UMETA(DisplayName = "Off"),
};

USTRUCT(BlueprintType)
struct FStructTest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float testingEnum;
};

/**
 * 
 */
class VRPROTO_API StructEnumBPExample
{
public:
	StructEnumBPExample();
	~StructEnumBPExample();
};
