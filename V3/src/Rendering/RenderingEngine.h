#pragma once
#include "GL/glew.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "..\Core\Application.h"
#include "..\Components\Renderer.h"
#include "Mesh.h"
#include <map>

class FrameBuffer;

/**
* @class RenderingEngine
* @brief Manages renderer and rendering mechanics
*
* @author Paolo Ferri
* @version 01
* @date 15/03/2019
*
*
* @bug No known bugs.
*/
class RenderingEngine 
{
public:
	static bool godRays;
	/**
	* @brief		Return the rendering engine instance
	* @pre			The instance is created
	* @post			The instance is returned
	* @return		The rendering engine instance
	*/
	static RenderingEngine& Instance();

	/**
	* @brief		Destroy the rendering engine object
	* @pre			The instance exists
	* @post			The instance is rdestroyed
	*/
	~RenderingEngine();

	/**
	* @brief		Initialize the rendering engine
	* @pre			The instance exists
	* @post			The instance is initialized
	*/
	void Initialize();

	/**
	* @brief		Render the current buffer of renderers with a specified material and all available cameras
	* @pre			The instance exists
	* @post			The renderers are drawn to the screen
	*/
	void RenderBuffer(MaterialType mt = DEFAULT);

	/**
	* @brief		Render the current buffer of renderers with a specified material and camera
	* @pre			The instance exists
	* @post			The renderers are drawn to the screen
	*/
	void RenderBuffer(Camera* camera, MaterialType mt = DEFAULT);	

	/**
	* @brief		Render the current buffer of renderers with a specified material and camera
	* @pre			The instance exists
	* @post			The renderers are drawn to the screen
	*/
	/**
	* @brief		Render the current buffer of renderers with a specified material and all available cameras
	* @pre			The instance exists
	* @post			The renderers are drawn to the screen
	*/
	void RenderBufferToTexture(MaterialType mt = DEFAULT);

	/**
	* @brief		Render the current buffer of renderers with a specified material and camera and force a color to the renderers
	* @pre			The instance exists
	* @post			The renderers are drawn to the screen with the color applied
	*/
	void RenderBufferOverrideColor(Camera* camera, glm::vec3 color, MaterialType mt = DEFAULT);

	/**
	* @brief		Add a renderer to the list of renderers to draw
	* @pre			The instance exists
	* @post			The renderer component is added to the list
	* @param rend		The renderer to be added
	*/
	void SubmitRenderer(Renderer* rend);

	/**
	* @brief		Clear the renderer list
	* @pre			The instance exists
	* @post			The renderer list is cleared
	*/
	void ClearRendererList();

	/**
	* @brief		The list of renderer components
	*/
	static std::vector<Renderer*> allRenderers;

private:
	/**
	* @brief		The lconstructor, private as this is a singleton
	*/
	RenderingEngine();

	RenderingEngine& operator=(const RenderingEngine& e) = delete;
	RenderingEngine(const RenderingEngine& e) = delete;

	/**
	* @brief		Helper method to render the list of renderer components
	* @pre			The instance exists
	* @post			The renderers are drawn to the screen
	* @param cam	The camera to be used for rendering
	* @param r		The vector to be render
	* @param m		The material type that the renderer components will use
	*/
	void RenderVector(Camera& cam, std::vector<Renderer*>& r, MaterialType m = MaterialType::DEFAULT);

	/**
	* @brief		Helper method to render the list of renderer components
	* @pre			The instance exists
	* @post			The renderers are drawn to the screen
	* @param cam	The camera to be used for rendering
	* @param r		The vector to be render
	* @param m		The material type that the renderer components will use
	* @param color		The color that will be applied to the material
	*/
	void RenderVectorOverrideColor(Camera& cam, std::vector<Renderer*>& r, glm::vec3 color,MaterialType m = MaterialType::DEFAULT);

	std::unique_ptr<Mesh> quadMesh;

};
