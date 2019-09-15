#pragma once
#include "DiagPrefab.h"
#include <list>
#include "..\Core\Camera.h"
class DiagRenderer
{
public:
	friend class RenderingEngine;
	static DiagRenderer& Instance();

	///Always call this in a LOGIC UPDATE!
	///This is because if you pause the scene, no objects will be deleted, but it's ok as the logic update won't run and no more objects are added
	///If this is called in other loops (like engine update) and the scene is paused, the memory will be flooded with diag spheres :)
	void RenderSphere(glm::vec3 pos, float scale = 1.0, glm::vec3 col = glm::vec3(1, 1, 1));


	void ClearAll();
private:
	void RenderAll(Camera& cam);
	std::list<std::unique_ptr<DiagPrefab>> allDiagPrefabs;
	DiagRenderer() {};
};