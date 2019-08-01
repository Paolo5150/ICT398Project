#include "Texture2D.h"
#include "FrameBuffer.h"
#include "Mesh.h"
#include <string>

class PostProcessStage
{
public:
	friend class PostProcessor;
	PostProcessStage(std::string name, Shader* shader, Mesh* quadMesh, bool HDR_FBO = false);
	Texture2D* Process(Texture2D* previous);

private:
	Shader* shader;
	std::unique_ptr<FrameBuffer> buffer;
	Mesh* quadMesh;

};