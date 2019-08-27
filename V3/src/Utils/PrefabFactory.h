#pragma once
#include "..\Prefabs\Bench.h"
#include "..\Prefabs\Chair.h"
#include "..\Prefabs\LandfillBin.h"
#include "..\Prefabs\RecycleBin.h"
#include "..\Prefabs\Table.h"
#include "..\Prefabs\Terrain.h"



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

		return nullptr;

	}
};