#include "pch.h"

#include "FileUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include  <string.h>
#include "PrefabFactory.h"
#include "../Emotion/NeedFactory.h"
#include "../Emotion/TraitFactory.h"


bool FileUtils::IsFileThere(std::string filePath)
{
	if (FILE *file = fopen(filePath.c_str(), "r")) {
		fclose(file);
		return true;
	}
	else {
		return false;
	}
}


std::string FileUtils::ReadFileToString(std::string filePath)
{
	std::string result = "";
	if (!IsFileThere(filePath))
		Logger::LogError("Could not read the file", filePath, ", file unavailable.");
	else
	{

		std::ifstream fs;
		fs.open(filePath);

		if (fs.is_open())
		{
			std::string line = "";

			while (!fs.eof())
			{

				std::getline(fs, line);
				result += line + "\n";
			}

			fs.close();

		}
		else
			Logger::LogError("Could not read the file",filePath);
	}



	return result;

}

std::string FileUtils::GetFileNameNoExtensionFromAbsolutePath(std::string path)
{
	std::string fileNameExt = GetFileNameFromAbsolutePath(path);
	int index = fileNameExt.find_last_of(".");
	std::string fileNameOnly = fileNameExt.substr(0, index);
	return fileNameOnly;

}


std::string FileUtils::GetFileNameFromAbsolutePath(std::string path)
{

	int index = path.find_last_of("\\/");
	std::string fileNameOnly = path.substr(index + 1, path.size());
	return fileNameOnly;
}

std::string FileUtils::GetLastFolderNameFromAbsolutePath(std::string path)
{
	size_t found;

	found = path.find_last_of("/\\");

	std::string folderName = path.substr(0, found);

	if (folderName.find_last_of("/\\") != 0)
		folderName = GetFileNameFromAbsolutePath(folderName);

	return folderName;

}

std::vector<ColliderInfo> FileUtils::ReadColliderFile(std::string absolutePathToFile)
{
	std::vector<ColliderInfo> trans;

	if (!IsFileThere(absolutePathToFile))
	{
		Logger::LogError("File", absolutePathToFile, "not found!!");
		return trans;
	}
	char buf[512];
	FILE* f;
	f = fopen(absolutePathToFile.c_str(), "r");

	glm::vec3 p, s, r;
	float mass;
	int rend;
	int isActive;

	char c;
	if (f != NULL)
	{
		while (!feof(f))
		{
			fgets(buf, 512, f);
			//Logger::LogInfo(buf[0],buf[1]);

			if (buf[0] == '#') continue;

			// If box collider
			if (buf[0] == 'B' && buf[1]=='C')
			{
				int lineInd = 6;
				// Read the next 4 lines
				while (lineInd > 0)
				{
					c = fgetc(f);
					if (c == 'P')
					{
						fscanf(f, "%f %f %f", &p.x, &p.y, &p.z);						
					}
					else if (c == 'S')
					{
						fscanf(f, "%f %f %f", &s.x, &s.y, &s.z);
					}
					else if (c == 'R')
					{
						fscanf(f, "%f %f %f", &r.x, &r.y, &r.z);
					}
					else if (c == 'M')
					{
						fscanf(f, "%f", &mass);
					}
					else if (c == 'D')
					{
						fscanf(f, "%d", &rend);
					}
					else if (c == 'A')
					{
						fscanf(f, "%d", &isActive);
					}
					lineInd--;
					fgets(buf, 512, f);
				}		

				trans.emplace_back("BC",p, s, r,mass,rend,isActive);
			}	
			else 			// If sphere collider
				if (buf[0] == 'S' && buf[1] == 'C')
				{
					int lineInd = 5;
					// Read the next 3 lines
					while (lineInd > 0)
					{
						c = fgetc(f);
						if (c == 'P')
						{
							fscanf(f, "%f %f %f", &p.x, &p.y, &p.z);
						}
						else if (c == 'S')
						{
							fscanf(f, "%f %f %f", &s.x, &s.y, &s.z);
						}
						else if (c == 'M')
						{
							fscanf(f, "%f", &mass);
						}
						else if (c == 'D')
						{
							fscanf(f, "%d", &rend);
						}
						else if (c == 'A')
						{
							fscanf(f, "%d", &isActive);
						}
						lineInd--;
						fgets(buf, 512, f);
					}

					trans.emplace_back("SC", p, s,mass, rend,isActive);
				}
		}
	}
	fclose(f);
	return trans;
}



std::vector<GameObject*> FileUtils::ReadSceneFile(std::string absolutePathToFile)
{
	std::vector<GameObject*> objs;

	if (!IsFileThere(absolutePathToFile))
	{
		Logger::LogError("File", absolutePathToFile, "not found!!");
		return objs;
	}
	char buf[512];
	FILE* f;
	f = fopen(absolutePathToFile.c_str(), "r");

	while (!feof(f))
	{
		char c = fgetc(f);

		char prefabName[100] = "";

		if (c == '#' || c == '\n')
		{
			if(c == '#')
				fgets(buf, 512, f);

			continue;
		}

		// Get prefab name
		for (int j = 0; j < 100; j++)
			{
				if (c != ' ')
					prefabName[j] = c;
				else
				{
					prefabName[j] = '\0';
					break;
				}
				c = fgetc(f);
			}

		glm::vec3 p, r,s;
		

		// Get prefab name
		for (int j = 0; j < 300; j++)
		{
			if (c == 'P')
			{
				fgetc(f); //Get rid of (
				fscanf(f, "%f,%f,%f", &p.x, &p.y, &p.z);
				fgetc(f); //Get rid of )
			}
			else if (c == 'R')
			{
				fgetc(f); //Get rid of (
				fscanf(f, "%f,%f,%f", &r.x, &r.y, &r.z);
				fgetc(f); //Get rid of )
			}
			else if (c == 'S')
			{
				fgetc(f); //Get rid of (
				fscanf(f, "%f,%f,%f", &s.x, &s.y, &s.z);

				// Scale is the last thing read, get out of loop
				fgets(buf, 512, f);
				break;
			}

			c = fgetc(f);
		}	

		GameObject* b = PrefabFactory::GetPrefabByName(prefabName);
		if (b != nullptr)
		{

			b->transform.SetPosition(p);
			b->transform.SetRotation(r);
			b->transform.SetScale(b->transform.GetScale().x * s.x, b->transform.GetScale().y * s.y, b->transform.GetScale().z * s.z);
			objs.push_back(b);
		}
		else
			Logger::LogError("Wrong prefab name in file", absolutePathToFile,": ",prefabName);
	}
	fclose(f);

	return objs;

}

bool FileUtils::ReadPersonalityFile(std::string absolutePathToFile, std::map<Need::NeedType, std::unique_ptr<Need>>& needs, std::list<std::unique_ptr<Trait>>& traits)
{
	if (!IsFileThere(absolutePathToFile))
	{
		Logger::LogError("File", absolutePathToFile, "not found!!");
		return false;
	}

	char buf[512];
	FILE* f;
	f = fopen(absolutePathToFile.c_str(), "r");

	char c;
	if (f != NULL)
	{
		while (!feof(f))
		{
			c = fgetc(f);

			if (c == '#')
			{
				fgets(buf, 512, f);
				continue;
			}

			std::string name;

			// If need
			if (c == 'N')
			{
				float startValue;
				int priority;
				float positiveGainMultiplier, negativeGainMultiplier;

				fscanf(f, "%s %f %d %f %f", &name, &startValue, &priority, &positiveGainMultiplier, &negativeGainMultiplier);

				//fgets(buf, 512, f);

				int needType = NeedFactory::GetNeedType(name);

				if (needType >= 0)
				{
					needs[(Need::NeedType)needType] = (std::move(NeedFactory::GetNeed((Need::NeedType) needType, startValue, priority, positiveGainMultiplier, negativeGainMultiplier)));
				}
			}
			// If trait
			else if (c == 'T')
			{
				fscanf(f, "%s", &name);

				//fgets(buf, 512, f);

				int traitType = TraitFactory::GetTraitType(name);

				if (traitType >= 0)
				{
					traits.push_back(std::move(TraitFactory::GetTrait((Trait::TraitType)traitType)));
				}
			}
			//fgets(buf, 512, f);
		}
		return true;
	}
	else
		return false;
}

