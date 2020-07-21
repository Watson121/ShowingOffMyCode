// Copyright of Adam Tedder 2020

#pragma once

#include "CoreMinimal.h"
#include "EngineUtils.h"

/**
 * 
 */

namespace PackageParameters {
	UENUM(BlueprintType)
	enum EPackageTypes {
		PACKAGE_Toy			UMETA(DisplayName = "Toy"),
		PACKAGE_Console		UMETA(DisplayName = "Console"),
		PACKAGE_Vase		UMETA(DisplayName = "Vase"),
	};

	UENUM(BlueprintType)
	enum EBoxTypes {
		BTYPE_BoxType1		UMETA(DisplayName = "Box Type 1"),
		BTYPE_BoxType2		UMETA(DisplayName = "Box Type 2"),
		BTYPE_BoxType3		UMETA(DisplayName = "Box Type 3"),
	};

	UENUM(BlueprintType)
	enum EDestinationCities {
		CITY_MarsCityOne	UMETA(DisplayName = "Mars City One"),
		CITY_MarsCityTwo	UMETA(DisplayName = "Mars City Two"),
		CITY_MarsCityThree	UMETA(DisplayName = "Mars City Three"),
		CITY_London			UMETA(DisplayName = "London"),
		CITY_Bristol		UMETA(DisplayName = "Bristol"),
		CITY_Machester		UMETA(DisplayName = "Manchester"),
		CITY_Liverpool		UMETA(DisplayName = "Liverpool"),
	};

	UENUM(BlueprintType)
	enum EChuteColour {
		COLOUR_Red			UMETA(DisplayName = "Red"),
		COLOUR_GREEN		UMETA(DisplayName = "Green"),
		COLOUR_BLUE			UMETA(DisplayName = "Blue"),
	};
}


class THANKYOUFORSERVICE_API EnumHolder
{
public:
	EnumHolder();
	~EnumHolder();
};



