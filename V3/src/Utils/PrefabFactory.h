#pragma once
#include "..\Prefabs\Bench.h"
#include "..\Prefabs\Chair.h"
#include "..\Prefabs\LandfillBin.h"
#include "..\Prefabs\RecycleBin.h"
#include "..\Prefabs\Table.h"
#include "..\Prefabs\Terrain.h"
#include "..\Prefabs\Water.h"
#include "..\Prefabs\Dylan.h"
#include "..\Prefabs\Drew.h"
#include "..\Prefabs\Paolo.h"
#include "..\Prefabs\DylanText.h"
#include "..\Prefabs\DrewText.h"
#include "..\Prefabs\PaoloText.h"
#include "..\Prefabs\Lantern.h"
#include "..\Prefabs\Fred.h"
#include "..\Prefabs\Riley.h"
#include "..\Prefabs\Joey.h"
#include "..\Prefabs\Box2.h"
#include "..\Prefabs\DrinkingFountain.h"

/**
* @class PrefabFactory
* @brief Factory used to get specific prefab object, by name
*
*
* @author Paolo Ferri
* @version 01
* @date 05/10/2019
*
*
* @bug No known bugs.
*/

class PrefabFactory
{
public:
	static GameObject* GetPrefabByName(std::string name)
	{
		if (name == "Bench")
		{
			return new Bench();
		}
		else if (name == "Chair")
		{
			return new Chair();
		}
		else if (name == "LandfillBin")
		{
			return new LandfillBin();
		}
		else if (name == "RecycleBin")
		{
			return new RecycleBin();
		}
		else if (name == "Table")
		{
			return new Table();
		}
		else if (name == "Dylan")
		{
			return new Dylan();
		}
		else if (name == "Paolo")
		{
			return new Paolo();
		}
		else if (name == "Drew")
		{
			return new Drew();
		}
		else if (name == "Water")
		{
			return new Water();
		}
		else if (name == "DylanText")
		{
			return new DylanText();
		}
		else if (name == "DrewText")
		{
			return new DrewText();
		}
		else if (name == "PaoloText")
		{
			return new PaoloText();
		}
		else if (name == "Lantern")
		{
			return new Lantern();
		}
		else if (name == "Fred")
		{
			return new Fred();
		}
		else if (name == "Joey")
		{
			return new Joey();
		}
		else if (name == "Riley")
		{
			return new Riley();
		}
		else if (name == "Box")
		{
			return new Box2();
		}
		else if (name == "DrinkingFountain")
		{
			return new DrinkingFountain();
		}

		return nullptr;

	}
};