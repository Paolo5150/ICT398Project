#pragma once

#include "Mesh.h"
#include "FrameBuffer.h"
#include "PostProcecssStage.h"
#include <list>
#include <functional>

class PostProcessor
{
public:
	static PostProcessor& Instance();

	void SetShader(std::string shader);
	void BindFrameBuffer() { sceneTexture->Bind(); }
	void UnbindFrameBuffer() { sceneTexture->Unbind(); }
	void RenderToScreen();


private:
	PostProcessor();
	std::unique_ptr<Mesh> quadMesh;

	std::unique_ptr<FrameBuffer> sceneTexture;
	Shader* currentPostProcessShader;
	std::list<PostProcessStage> postsProcessStages;

};