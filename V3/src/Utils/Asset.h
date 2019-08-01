#pragma once
#include <string>
#include "..\Core\Logger.h"

/**
* @class Asset
* @brief Generic class for an Asset item
*
*
* @author Paolo Ferri
* @version 01
* @date 21/03/2019
*
*
* @bug No known bugs.
*/

class Asset
{
public:
	/**
	* @brief Create the asset object
	*
	* @post The asset object is created
	*/
	Asset(){};
	/**
	* @brief Destroy the asset object
	*
	* @pre The asset object exists
	* @post The asset object is destroyed
	*/
	virtual ~Asset(){ /*Logger::LogInfo("Delete asset", name);*/ };

	/**
	* @brief The asset name
	*/
	std::string name;

};


/**
* @class Asset
* @brief Specialized class for an internal Asset
* Internal assets are assets that are not crated from external files
*
*
* @author Paolo Ferri
* @version 01
* @date 21/03/2019
*
*
* @bug No known bugs.
*/

class InternalAsset : public Asset
{
public:
	/**
	* @brief Create the asset object
	*
	* @post The asset object is created
	*/
	InternalAsset(){};

	/**
	* @brief Destroy the asset object
	*
	* @pre The asset object exists
	* @post The asset object is destroyed
	*/
	virtual ~InternalAsset(){ /*Logger::LogInfo("Delete asset", name);*/ };

};