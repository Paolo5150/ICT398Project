#pragma once
#include "DiagPrefab.h"
#include <list>
#include "..\Core\Camera.h"
class DiagRenderer
{
public:
	friend class RenderingEngine;
	static DiagRenderer& Instance();

	void RenderSphere(glm::vec3 pos, float scale = 1.0, glm::vec3 col = glm::vec3(1, 1, 1));


private:
	void RenderAll(Camera& cam);
	void ClearAll();
	std::list<std::unique_ptr<DiagPrefab>> allDiagPrefabs;
	DiagRenderer() {};
};