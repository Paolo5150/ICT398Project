#include "pch.h"

#include "UniformBufferGL.h"
#include "..\Core\Logger.h"

UniformBufferGL::UniformBufferGL(unsigned totalSize, unsigned binding) : UniformBuffer(totalSize,binding)
{
	glGenBuffers(1, &m_id);
	glBindBuffer(GL_UNIFORM_BUFFER, m_id);

	glBufferData(GL_UNIFORM_BUFFER, totalSize, NULL, GL_DYNAMIC_DRAW);
	glBindBufferRange(GL_UNIFORM_BUFFER, binding, m_id, 0, totalSize);

}

UniformBufferGL::~UniformBufferGL()
{
	glDeleteBuffers(1, &m_id);
	//Logger::LogError("Deleted UBO");
}

void UniformBufferGL::AddDataRange(unsigned stride, unsigned dataSize, const void* data)
{
	glBufferSubData(GL_UNIFORM_BUFFER, stride, dataSize, data);

}
void UniformBufferGL::Bind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, m_id);

}
void UniformBufferGL::Unbind()
{
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

}