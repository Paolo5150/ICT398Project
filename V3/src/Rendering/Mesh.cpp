#include "pch.h"

#include "Mesh.h"
#include "..\Core\Core.h"

Mesh::Mesh(std::vector<Vertex> vs, std::vector<unsigned> inds, bool calculateNormals)
{
	vertices = vs;
	indices = inds;

	if (calculateNormals)
		CalculateNormals();

	InitializeVertexArray();

}

Mesh::~Mesh()
{
	if (bones_id_weights_for_each_vertex.size() > 0)
		glDeleteBuffers(1, &VBO_bones);

//	Logger::LogError("Mesh", name, "died");

}

void Mesh::Render(Camera& cam)
{
	vertexArray->RenderArrayTriangles(indices.size());
}
void Mesh::Render()
{
	vertexArray->RenderArrayTriangles(indices.size());

}



glm::vec3 Mesh::GetCenter()
{
	glm::vec3 center;

	for (int i = 0; i < vertices.size(); i++)
	{
		center += vertices[i].position;

	}

	center /= vertices.size();
	return center;

}


void Mesh::InitializeVertexArray()
{
	vertexArray = std::unique_ptr<VertexArray>(Core::Instance().GetGraphicsAPI().CreateVertexArray());
	vertexBuffer = std::unique_ptr<ArrayBuffer<Vertex>>(Core::Instance().GetGraphicsAPI().CreateVertexBuffer());
	indexBuffer = std::unique_ptr<ArrayBuffer<unsigned>>(Core::Instance().GetGraphicsAPI().CreateIndexBuffer());



	vertexArray->Bind();
	vertexBuffer->AddData(vertices);
	indexBuffer->AddData(indices);

	//Position
	vertexArray->AddLayoutf(0, 3, false, sizeof(Vertex), 0);

	//normal
	vertexArray->AddLayoutf(1, 3, false, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	//UV
	vertexArray->AddLayoutf(2, 2, false, sizeof(Vertex), (void*)offsetof(Vertex, UV));

	//color
	vertexArray->AddLayoutf(3, 3, false, sizeof(Vertex), (void*)offsetof(Vertex, color));

	//tangent
	vertexArray->AddLayoutf(4, 3, false, sizeof(Vertex), (void*)offsetof(Vertex, tangent));

	//bitangemnt
	vertexArray->AddLayoutf(5, 3, false, sizeof(Vertex), (void*)offsetof(Vertex, binormal));

	/*Bones*/
	//bones data
	if (bones_id_weights_for_each_vertex.size() > 0)
	{
		glGenBuffers(1, &VBO_bones);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
		glBufferData(GL_ARRAY_BUFFER, bones_id_weights_for_each_vertex.size() * sizeof(bones_id_weights_for_each_vertex[0]), &bones_id_weights_for_each_vertex[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	if (bones_id_weights_for_each_vertex.size() > 0)
	{
	//bones
	glBindBuffer(GL_ARRAY_BUFFER, VBO_bones);
	glEnableVertexAttribArray(6);
	glVertexAttribIPointer(6, 4, GL_UNSIGNED_INT, sizeof(VertexBoneData), (GLvoid*)0); // for INT Ipointer
	glEnableVertexAttribArray(7);
	glVertexAttribPointer(7, 4, GL_FLOAT, GL_FALSE, sizeof(VertexBoneData), (const GLvoid*)(16));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	vertexArray->Unbind();
}


void Mesh::CalculateNormals()
{
	if (indices.size() > 3)
	{

		for (unsigned int i = 0; i < indices.size() - 2; i += 3)
		{
			//Normals
			glm::vec3 v1v2 = vertices[indices[i + 1]].position - vertices[indices[i]].position;
			glm::vec3 v1v3 = vertices[indices[i + 2]].position - vertices[indices[i]].position;
			glm::vec3 cross = glm::normalize(glm::cross(v1v2, v1v3));


			vertices[indices[i]].normal = cross;
			vertices[indices[i + 1]].normal = cross;
			vertices[indices[i + 2]].normal = cross;

			//Tangent and binormal
			glm::vec2 deltaUV1 = vertices[indices[i + 1]].UV - vertices[indices[i]].UV;
			glm::vec2 deltaUV2 = vertices[indices[i + 2]].UV - vertices[indices[i]].UV;

			float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);

			vertices[indices[i]].tangent = r * ((v1v2 * deltaUV2.y) - (v1v3 * deltaUV1.y));
			vertices[indices[i + 1]].tangent = r * ((v1v2 * deltaUV2.y) - (v1v3 * deltaUV1.y));
			vertices[indices[i + 2]].tangent = r * ((v1v2 * deltaUV2.y) - (v1v3 * deltaUV1.y));

			vertices[indices[i]].binormal = r * ((v1v3 * deltaUV1.x) - (v1v2 * deltaUV2.x));
			vertices[indices[i + 1]].binormal = r * ((v1v3 * deltaUV1.x) - (v1v2 * deltaUV2.x));
			vertices[indices[i + 2]].binormal = r * ((v1v3 * deltaUV1.x) - (v1v2 * deltaUV2.x));

		}
	}
}

void VertexBoneData::addBoneData(unsigned bone_id, float weight)
{
	for (unsigned i = 0; i < NUM_BONES_PER_VEREX; i++)
	{
		if (weights[i] == 0.0)
		{
			ids[i] = bone_id;
			weights[i] = weight;

			return;
		}
	}

}