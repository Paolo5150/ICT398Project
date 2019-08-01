#include "pch.h"
#include "MeshRenderer.h"
#include "..\Core\Core.h"



MeshRenderer::~MeshRenderer()
{
	//Logger::LogError("Deleted mesh renderer of", _parent->name);
}
MeshRenderer::MeshRenderer(Mesh* m, Material mat, bool isCullable) : Renderer("MeshRenderer", mat)
{	
	this->isCullable = isCullable;
	SetMesh(m);
}

void MeshRenderer::SetMesh(Mesh* m)
{
	mesh = m;
}



void MeshRenderer::Initialize()
{
	
}

Mesh& MeshRenderer::GetMesh()
{
	return *mesh;
}

void MeshRenderer::Render(Camera& cam)
{	
	mesh->Render(cam);
}