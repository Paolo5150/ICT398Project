#pragma once
#include "..\Core\Logger.h"
#include <fstream>
#include <iostream>
#include <assert.h>
#include <filesystem>
#include <windows.h>
#include "Maths.h"
#include "..\Core\ColliderInfo.h"
#include "..\Core\GameObject.h"
#include "..\Components\AIEmotion.h"

/**
* @class FileUtils
* @brief Helper class used for accessing external files
*
*
* @author Paolo Ferri
* @version 01
* @date 05/03/2019
*
*
* @bug No known bugs.
*/
class FileUtils
	{
	public:
		/**
		* @brief						Check if the file is available
		* @param filePath				The absolute path to the file
		* @return						True if the file is available
		*/
		static bool IsFileThere(std::string filePath);

		/**
		* @brief						Reads the content of a file and returns it as string
		* @post							The content of the file as String and the file is left unchanged
		* @param filePath				The absolute path to the file
		* @return						The content of the file as String
		*/
		static std::string ReadFileToString(std::string filePath);

		/**
		* @brief						Returns the path to the current directory	
		* @return						The path to the current directory	
		*/
		static std::string GetCurrentDir();
		//static void PrintFiles(std::string folder);

		/**
		* @brief						Returns the file name given an absolute path
		* @pre							The file is available
		* @post							The name of the file is returned
		* @param path					The absolute path
		* @return						The name of the file
		*/
		static std::string GetFileNameFromAbsolutePath(std::string path);

		/**
		* @brief						Returns the file name with no extension given an absolute path
		* @pre							The file is available
		* @param path					The absolute path
		* @post							The name of the file with no extension is returned
		* @return						The name of the file with no extension
		*/
		static std::string GetFileNameNoExtensionFromAbsolutePath(std::string path);

		/**
		* @brief						Returns the folder name given an absolute path
		* @pre							The file is available
		* @post							The name of the folder is returned
		* @param path					The absolute path
		* @return						The name of the folder
		*/
		static std::string GetLastFolderNameFromAbsolutePath(std::string path);

		/**
		* @brief						Returns a vector of colliders, read from file
		* @pre							The file is available
		* @param absolutePathToFile		The absolute path to the file
		* @return						The vector of colliders, read from file
		*/
		static std::vector<ColliderInfo> ReadColliderFile(std::string absolutePathToFile);

		/**
		* @brief						Returns a vector of gameobjects to be added to the scene, read from file
		* @pre							The file is available
		* @param absolutePathToFile		The absolute path to the file
		* @return						The vector of game objects, read from file
		*/
		static std::vector<GameObject*> ReadSceneFile(std::string absolutePathToFile);

		/**
		* @brief						Loads the data in the given file and converts it into a format accepted by the passed in reference variables
		* @pre							The file is available
		* @post							Loads the given data structures if possible
		* @param absolutePathToFile		The absolute path to the file
		* @param needs					Map that the read needs will be loaded into
		* @param trait					List that the read Traits will be loaded into
		* @return						Whether the file was read and data structures loaded
		*/
		static bool ReadPersonalityFile(std::string absolutePathToFile, std::map<Need::NeedType, std::unique_ptr<Need>>& needs, std::list<std::unique_ptr<Trait>>& traits);


		/**
		* @brief						Returns the class name of an object
		* @pre							The object is not null
		* @post							The class name of an object is returned
		* @param obj					The object
		* @return						The  class name of an object
		*/
		template <class T>
		static std::string GetClassName(T* obj = nullptr)
		{
			std::string n;
			if (obj == nullptr)
			{
				n = typeid(T).name();
				n = n.substr(6, n.length());
			}
			else
			{
				n = typeid(*obj).name();
				n = n.substr(6, n.length());
			}
			return n;
		}
};


