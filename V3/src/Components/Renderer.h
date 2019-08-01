#pragma once
#include "..\Core\Component.h"
#include "..\Rendering\Material.h"
#include <map>
#include <functional>
#include <vector>

class Camera;
class Shader;

/**
* @class Renderer
* @brief Generic render class for rendering objects
*
*
* @author Paolo Ferri
* @version 01
* @date 28/02/2019
*
* @bug No known bugs.
*/

class Renderer : public Component
	{
	public:
		friend class RenderingEngine;

		/**
		* @brief		Create new Renderer component
		*
		* @post			The Renderer compnent is created
		*
		* @param name	The name of the spceialized renderer component
		* @param m		The material used to render the object
		*/
		Renderer(std::string name, Material m);

		/**
		* @brief		Create new Renderer component
		*
		* @post			The Renderer compnent is created
		*
		* @param name	The name of the spceialized renderer component
		*/
		Renderer(std::string name);

		/**
		* @brief		Destroy the material and mesh
		*
		* @pre			The material and mesh exist
		* @post			The material and mesh are destroyed
		*/
		virtual ~Renderer() {};

		/**
		* @brief		Render abstract method
		*
		* @pre			The component exists and attached to a gameobject
		* @post			The object is rendered
		*
		* @param cam	The camera used to render the object
		*/
		virtual void Render(Camera& cam) = 0;
		
		/**
		* @brief		Callback called right before the Render method
		*
		* @pre			The render mmethod has not been called
		* @post			The method is called before Render
		*
		* @param cam	The camera used to render the object
		* @param currentShader	The shader used to render the object
		*/
		virtual void OnPreRender(Camera& cam, Shader* currentShader = nullptr) ;

		/**
		* @brief		Callback called right after the Render method
		*
		* @pre			The render mmethod has been called
		* @post			The method is called after Render
		*
		* @param cam	The camera used to render the object
		* @param currentShader	The shader used to render the object
		*/
		virtual void OnPostRender(Camera& cam, Shader* currentShader = nullptr);

		/**
		* @brief		Overridable method called every frame
		*
		* @pre			The component exists, is active and attached to a gameobject
		*/
		void Update() override;

		/**
		* @brief		 Check for culling and send renderer to rendering engine
		*
		* @pre			The component exists, is active and attached to a gameobject
		* @post			The component is send to the rendering engine for rendering.
		*
		*/
		void EngineUpdate() override;

		/**
		* @brief		Return the material of specified category
		*
		* @pre			The component exists, is active and attached to a gameobject
		* @post			The material is returned
		*
		* @param materialType	The type of material to be returned
		*/
		Material& GetMaterial(MaterialType materialType = DEFAULT);

		/**
		* @brief		Set the material of specified category
		*
		* @pre			The component exists, is active and attached to a gameobject
		* @post			The material is set
		*
		* @param m		The new material
		* @param materialType	The type of material to be returned
		*/
		void SetMaterial(Material m, MaterialType = DEFAULT);

		/**
		* @brief		Add callback to list of listener for the PreRender method
		*
		* @pre			The callback is a valid function
		* @post			The callback is added to the list
		*
		* @param cb		The callback function
		*/
		void AddPreRenderCallback(std::function<void(Camera&, Shader*)> cb);

		/**
		* @brief		Add callback to list of listener for the PostRender method
		*
		* @pre			The callback is a valid function
		* @post			The callback is added to the list
		*
		* @param cb		The callback function
		*/
		void AddPostRenderCallback(std::function<void(Camera&, Shader*)> cb);

		/**
		* @brief		Return isCullable
		*/
		bool GetIsCullable() { return isCullable; }

		/**
		* @brief		Set isCullable
		*
		* @post			isCullable is set to a new value
		* @param		The new value
		*/
		void SetIsCullable(bool ic){ isCullable = ic; }

		void OnAttach(GameObject* go) override;

		Transform* transform;


	protected:
		/**
		* @brief		All the materials used by the Renderer
		*/
		std::map<int, Material> allMaterials;

		/**
		* @brief		All the PreRender calblacks
		*/
		std::vector<std::function<void(Camera&, Shader*)>> preRenderCallbacks;

		/**
		* @brief		All the PostRender callbacks
		*/
		std::vector<std::function<void(Camera&, Shader*)>> postRenderCallbacks;

		/**
		* @brief		Whether the component has been submitted to the rendering engine
		*/
		bool submitted;

		/**
		* @brief		Whether the component will be culled during rendering
		*/
		bool isCullable;

	private:

		/**
		* @brief		Create simplified material based on default one
		*
		* @pre			The default material exists
		* @post			The simplified materials are created
		*
		* @param defaultMat	The default material
		*/
		void CreateOtherMaterials(Material& defaultMat);
};

