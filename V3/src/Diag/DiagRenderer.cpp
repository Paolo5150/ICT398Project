#include "pch.h"
#include "DiagRenderer.h"
#include "DiagSphere.h"

DiagRenderer& DiagRenderer::Instance()
{
	static DiagRenderer instance;
	return instance;
}

void  DiagRenderer::RenderSphere(glm::vec3 pos, float scale, glm::vec3 col)
{
	DiagSphere* ds = new DiagSphere(pos, scale, col);
	ds->transform.SetPosition(pos);
	ds->transform.SetScale(scale);
	ds->meshRenderer->GetMaterial().SetColor(col.x, col.y, col.z);
	allDiagPrefabs.push_back(std::unique_ptr<DiagPrefab>(ds));
}

void DiagRenderer::RenderAll(Camera& cam)
{
	auto it = allDiagPrefabs.begin();

	for (; it != allDiagPrefabs.end(); it++)
	{
		glm::mat4 mvp = cam.GetProjectionMatrix() * cam.GetViewMatrix() * (*it)->transform.GetMatrix();
		(*it)->meshRenderer->GetMaterial().BindMaterial();
		(*it)->meshRenderer->GetMaterial().GetShader().SetMat4("u_mvp", mvp);
		(*it)->meshRenderer->GetMaterial().GetShader().SetMat4("u_model", (*it)->transform.GetMatrix());
		(*it)->meshRenderer->GetMaterial().GetShader().SetMat4("u_view", cam.GetViewMatrix());
		(*it)->meshRenderer->GetMaterial().GetShader().SetMat4("u_projection", cam.GetProjectionMatrix());
		(*it)->meshRenderer->GetMesh().Render();
	}
}
void DiagRenderer::ClearAll()
{
	allDiagPrefabs.clear();

}
