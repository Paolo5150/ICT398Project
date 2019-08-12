#include "pch.h"
#include "GridMesh.h"
#include "..\Core\Logger.h"


GridMesh::GridMesh(int widthVerts, int depthVerts)
{
	sizeX = widthVerts;
	sizeZ = depthVerts;

	Initialize();
	InitializeVertexArray();
}

GridMesh::~GridMesh()
{

}

void GridMesh::Initialize()
{
	for (int x = 0; x < sizeX; x++)
	{

		for (int z = 0; z < sizeZ; z++)
		{
			Vertex v;
			v.position = glm::vec3(x, 0, z);
			//v.normal = glm::vec3(0, 1, 0);
			v.color = glm::vec3(1, 1, 1);
			v.UV.x = x / (float)(sizeX - 1);
			v.UV.y = z / (float)(sizeZ - 1);
			vertices.push_back(v);
		}
	}

	int indexIndex = 0;
	int counter = 0;
	for (unsigned int i = 0; i < vertices.size(); i++)
	{

		if (counter >= sizeX - 1)
		{
			counter = 0;
			continue;
		}

		if (i >= vertices.size() - sizeX - 1)
			break;

		//Face 1

		indices.push_back(i);
		indices.push_back(i + 1);
		indices.push_back(i + sizeX + 1);

		//Face 2
		indices.push_back(i + sizeX + 1);
		indices.push_back(i + sizeX);
		indices.push_back(i);
		counter++;
	}

	Logger::LogInfo("End of grid mesh, size", vertices.size());
	CalculateNormals();
}