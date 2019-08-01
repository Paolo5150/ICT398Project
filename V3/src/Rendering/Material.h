#pragma once

#include "Texture2D.h"
#include"Shader.h"
#include "CubeMap.h"
#include "EquirectangularMap.h"
#include <unordered_map>
#include <string>



	class Model;


	enum MaterialType
	{
		DEFAULT,
		NOLIGHT,
		COLORONLY
	};

	/**
	* @class Material
	* @brief Describe the look of an object when it's rendered
	*
	* @author Paolo Ferri
	* @version 01
	* @date 15/03/2019
	*
	*
	* @bug No known bugs.
	*/

	class Material : public InternalAsset
	{

	public:
		friend class MeshMaterial;
		friend class Model;
		friend class AssimpWrapper;

		/**
		* @brief Load texture into the material
		*
		* @pre	The material exist, the texture is not null
		* @post The texture is loaded into the material
		* @param t	The texture to be loaded
		* @param ty The texture uniform used by the shader
		*/
		void Loadtexture(Texture2D* t, std::string uniformName = "diffuse0");


		/**
		* @brief Load cubemap into the material
		*
		* @pre	The material exist, the texture is not null
		* @post The cubemap is loaded into the material
		* @param t	The cubemap to be loaded
		* @param ty The texture uniform used by the shader
		*/
		void LoadCubemap(CubeMap* t, std::string uniformName = "cubeMap0");

		/**
* @brief Load cubemap into the material
*
* @pre	The material exist, the texture is not null
* @post The cubemap is loaded into the material
* @param t	The cubemap to be loaded
* @param ty The texture uniform used by the shader
*/
		void LoadEquirectangularMap(EquirectangularMap* t, std::string uniformName = "environment0");

		/**
		* @brief Create material object
		*
		* @post The material is created
		*/
		Material();

		/**
		* @brief Create material object
		*
		* @post The material is created
		* @param s	The material shader
		*/
		Material(Shader* s);

		/**
		* @brief Destroy material object
		*
		* @pre	The material exist
		* @post The material is destroyed
		*/
		virtual ~Material();

		/**
		* @brief Bind shader, textures and cubemap in the material
		*
		* @pre	The material exist
		* @post The material is ready to be used
		*/
		void BindMaterial();

		/**
		* @brief UnBind shader, textures and cubemap in the material
		*
		* @pre	The material exist
		* @post The material is disabled
		*/
		void UnbindMaterial();


		/**
		* @brief Set the material shader
		*
		* @pre	The material exist
		* @post The material shader is set
		* @param s The new shader
		*/
		void SetShader(Shader* s) { shader = s; }

		/**
		* @brief Get the material shader
		*
		* @pre	The material exist
		* @post The material shader is returned
		* @return The new shader
		*/
		Shader& GetShader() { return *shader; };

		/**
		* @brief Load a vec4 value into the material
		*
		* @pre	The material exist
		* @post The material is loaded with the value
		* @param n The name of the value to be referenced in the shader
		* @param v The value to be loaded
		*/
		void LoadVec4(std::string n, glm::vec4 v);


		/**
		* @brief Load a vec3 value into the material
		*
		* @pre	The material exist
		* @post The material is loaded with the value
		* @param n The name of the value to be referenced in the shader
		* @param x The x value of the vec3 to be loaded
		* @param y The y value of the vec3 to be loaded
		* @param z The z value of the vec3 to be loaded
		*/
		void LoadVec3(std::string n, float x, float y, float z);

		/**
		* @brief Load a float value into the material
		*
		* @pre	The material exist
		* @post The material is loaded with the value
		* @param n The name of the value to be referenced in the shader
		* @param v The value to be loaded
		*/
		void LoadFloat(std::string n, float v);

		/**
		* @brief Load a matrix 4x4 value into the material
		*
		* @pre	The material exist
		* @post The material is loaded with the value
		* @param n The name of the value to be referenced in the shader
		* @param v The value to be loaded
		*/
		void LoadMat4(std::string n, glm::mat4 v);

		/**
		* @brief Set the material color
		* Will use LoadVec3 to set a color variable
		*
		* @pre	The material exist
		* @post The material is loaded with the color
		* @param r The red channel of the color
		* @param g The green channel of the color
		* @param v The blue channel of the color
		*/
		void SetColor(float r, float g, float b);

		/**
		* @brief Get the material color
		* Will use LoadVec3 to set a color variable
		*
		* @pre	The material exist
		* @post The material color is returned
		* @param r The red channel of the returned color
		* @param g The green channel of the returned color
		* @param v The blue channel of the returned color
		*/
		void GetColor(float& r, float &g, float& b);

	protected:
		/**
		* @brief The material textures
		*/
		std::unordered_map<std::string, Texture2D*> textures;

		/**
		* @brief The material cubemaps
		*/
		std::unordered_map<std::string, CubeMap*> cubemaps;

		/**
* @brief The material cubemaps
*/
		std::unordered_map<std::string, EquirectangularMap*> equirectMaps;

		/**
		* @brief The material shader
		*/
		Shader* shader;

		/**
		* @brief The material vec4s
		*/
		std::unordered_map<std::string, glm::vec4> vec4s;

		/**
		* @brief The material vec3s
		*/
		std::unordered_map<std::string, glm::vec3> vec3s;

		/**
		* @brief The material floats
		*/
		std::unordered_map<std::string, float> floats;

		/**
		* @brief The material matrices 4x4
		*/
		std::unordered_map<std::string, glm::mat4> mat4s;
	
		/**
		* @brief Pre load material with default values
		*
		* @pre	The material exist
		* @post The material is pre loaded
		*/
		void PreloadMaterial();
	};
