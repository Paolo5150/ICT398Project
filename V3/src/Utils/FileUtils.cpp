#include "pch.h"

#include "FileUtils.h"
#include <stdio.h>
#include <stdlib.h>
#include  <string.h>


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
	char buf[100];
	FILE* f;
	f = fopen(absolutePathToFile.c_str(), "r");

	glm::vec3 p, s, r;
	int rend;
	char c;
	if (f != NULL)
	{
		while (!feof(f))
		{
			fgets(buf, 100, f);
			//Logger::LogInfo(buf[0],buf[1]);

			// If box collider
			if (buf[0] == 'B' && buf[1]=='C')
			{
				int lineInd = 4;
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
					else if (c == 'D')
					{
						fscanf(f, "%d", &rend);
					}
					lineInd--;
					fgets(buf, 512, f);
				}		

				trans.emplace_back("BC",p, s, r,rend);
			}	
			else 			// If sphere collider
				if (buf[0] == 'S' && buf[1] == 'C')
				{
					int lineInd = 3;
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
						else if (c == 'D')
						{
							fscanf(f, "%d", &rend);
						}
						lineInd--;
						fgets(buf, 512, f);
					}

					trans.emplace_back("SC", p, s, rend);
				}
		}
	}

	return trans;
}
