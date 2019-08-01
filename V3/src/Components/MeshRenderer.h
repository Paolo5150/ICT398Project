#pragma once
#include "Renderer.h"
#include "..\Rendering\Mesh.h"

/**
* @class MeshRenderer
* @brief Specialized Renderer used to render meshes
*
*
* @author Paolo Ferri
* @version 01
* @date 28/02/2019
*
* @bug No known bugs.
*/

class MeshRenderer : public Renderer
	{

	public:
		friend class RenderingEngine;

		/**
		* @brief		Clean up vertex array from memoery
		*
		* @post			The vertices are removed from memory.
		*/
		~MeshRenderer();

		/**
		* @brief		Create MeshRenderer component
		*
		* @post			The MeshRenderer component is created
		*
		* @param m		The mesh to be rendered
		* @param mat	The material used to render the object
		* @param isCullable	Whether the mesh should be culled
		*/
		MeshRenderer(Mesh* m, Material mat, bool isCullable = true);

		/**
		* @brief		Create MeshRenderer component
		* @pre			The MeshRenderer exists and attached to a GameObject
		* @post			The MeshRenderer component is rendered
		*
		* @param cam		The camera used to render the mesh
		*/
		void Render(Camera& cam) override;

		/**
		* @brief		Return the mesh
		* @pre			The mesh exists
		* @post			The mesh is returned
		*/
		Mesh& GetMesh();

		/**
		* @brief		Set a new mesh for the renderer
		* @pre			The mesh passed in exists
		* @post			The old mesh is replaced with the new one
		*
		* @param m		The new mesh
		*/
		void SetMesh(Mesh* m);

	private:

		/**
		* @brief		The mesh
		*/
		Mesh* mesh;


		
		/**
		* @brief		Initialize vertex array and load vertices
		*
		* @pre			The vertices are defined
		* @post			The vertives are loaded to GPU
		*/
		void Initialize();



	};

