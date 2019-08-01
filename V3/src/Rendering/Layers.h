#pragma once

struct RenderingLayers
{
	enum LayerNames
	{
		DEFAULT = 1 << 0,
		WATER = 1 << 1,
		GUI = 1 << 2,
		TERRAIN = 1 << 3,
		SKYBOX = 1 << 4,
		GUN = 1 << 5
	};
};