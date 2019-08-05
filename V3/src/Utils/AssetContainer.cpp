#include "pch.h"

#include "AssetContainer.h"

void AssetContainer::UnloadVolatile()
{
	volatileAssets.clear();
}

void AssetContainer::LoadRaw(std::string name, Asset* asset, bool isPersistent)
{
	std::unique_ptr<Asset> m_unique(asset);

	if (!isPersistent)
		volatileAssets[name] = std::move(m_unique);
	else
		persistendAssets[name] = std::move(m_unique);
}


void AssetContainer::Load(std::string name, std::unique_ptr<Asset>& asset, bool isPersistent)
{
	auto itV = volatileAssets.find(name);
	auto itP = persistendAssets.find(name);


	if (!isPersistent)
	{
		if(itV == volatileAssets.end())
			volatileAssets[name] = std::move(asset);

	}
	else if(itP == persistendAssets.end())
		persistendAssets[name] = std::move(asset);

}

void AssetContainer::UnloadPersistent()
{
	persistendAssets.clear();
}

void AssetContainer::PrintAllNames()
{
	for (auto it = volatileAssets.begin(); it != volatileAssets.end(); it++)
	{
		Logger::LogInfo(it->second->name);
	}

	for (auto it = persistendAssets.begin(); it != persistendAssets.end(); it++)
	{
		Logger::LogInfo(it->second->name);
	}
}

