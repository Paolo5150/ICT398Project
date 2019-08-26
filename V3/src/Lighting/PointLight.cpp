#include "pch.h"

#include "PointLight.h"
#include "..\Components\MeshRenderer.h"
#include "..\Utils\ContentManager.h"
#include "..\Diag\DiagRenderer.h"

PointLight::PointLight() : Light("PointLight",POINT)
{

	intensity = 20.0f;
	lightType = POINT;

}
PointLight::~PointLight()
{

}

void PointLight::RenderDiag()
{
	DiagRenderer::Instance().RenderSphere(transform.GetPosition(), 0.5f, GetDiffuseColor());
}


