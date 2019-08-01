#pragma once
#include <map>
#include <string>
#include "Asset.h"

/**
* @class AssetContainer
* @brief Container class for Asset objects
*
*
* @author Paolo Ferri
* @version 01
* @date 05/03/2019
*
* @bug No known bugs.
*/
class AssetContainer
{
public:
	friend class ContentManager;
	/**
	* @brief		Creates a container for external assets
	*
	* @post			The container object is created
	*/
	AssetContainer(){};

	/**
	* @brief		Destroy the container
	* @pre			The container exists
	* @post			The container object is created
	*/
	~AssetContainer(){};

	/**
	* @brief		Load an asset into the container
	* @pre			The container exists, the asset is no null
	* @post			The asset is loaded into the container
	*/
	void Load(std::string name, std::unique_ptr<Asset>& asset, bool isPersistent = false);

		/**
	* @brief		Load an asset into the container
	* @pre			The container exists, the asset is no null
	* @post			The asset is loaded into the container
	*/
	void LoadRaw(std::string name, Asset* asset, bool isPersistent = false);

	/**
	* @brief		Get asset of specific type
	* @pre			The container exists, the asset is in the container
	* @post			The asset is returned
	* @param name	The asset's name
	* @return		The asset requested
	*/
	template<class T>
	T* GetAsset(std::string name);

	/**
	* @brief		unload all assets flagged not preserved in the container
	* @pre			The container exists
	* @post			The non preserved assets are unloaded
	*/
	void UnloadVolatile();

	void PrintAllNames();


private:
		/**
	* @brief		Unload all assets flagged preserved in the container
	* @pre			The container exists
	* @post			The preserved assets are unloaded
	*/
	void UnloadPersistent();
	/*
	* @breif The list of assets
	*/
	std::map<std::string, std::unique_ptr<Asset>> volatileAssets;

	/*
* @breif The list of assets
*/
	std::map<std::string, std::unique_ptr<Asset>> persistendAssets;
};





template <class T>
T* AssetContainer::GetAsset(std::string name)
{
	auto it = volatileAssets.find(name);

	if (it != volatileAssets.end())
		return (T*)it->second.get();
	else
	{
		auto it2 = persistendAssets.find(name);

		if (it2 != persistendAssets.end())
			return (T*)it2->second.get();

	}
	return nullptr;
}


