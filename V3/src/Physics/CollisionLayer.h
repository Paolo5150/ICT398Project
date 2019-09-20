#pragma once

struct CollisionLayers
{
	enum CollisionLayerNames
	{
		DEFAULT = 1 << 1,
		OBSTACLE = 1 << 2,
		CAMERA = 1 << 3,
		PATHNODE = 1 << 3
	};
};