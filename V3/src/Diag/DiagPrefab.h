#pragma once

#include <iostream>
#include "..\Components\MeshRenderer.h"
#include "..\Utils\Maths.h"
#include "..\Utils\ContentManager.h"
#include "..\Core\Transform.h"

class DiagPrefab
{
public:
	DiagPrefab();
	virtual ~DiagPrefab();
	Transform transform;
	std::unique_ptr<MeshRenderer> meshRenderer;
	glm::vec3 color;

protected:
	Material material;

};