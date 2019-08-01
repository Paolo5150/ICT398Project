#pragma once

struct CollisionLayers
{
	enum CollisionLayerNames
	{
		DEFAULT = 1 << 0,
		PLAYER = 1 << 1,
		ENEMY = 1 << 2,
		OBSTACLE = 1 << 3,
		PATHNODE = 1 << 4,
		PUPMKIN = 1 << 5,
		SPIDER = 1 << 6,
		LAUNCHER = 1 << 7,
		COMPANION = 1 << 8,
		TARGETER = 1 << 9,
		HIVE = 1 << 10
	};
};