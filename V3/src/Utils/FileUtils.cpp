#include "pch.h"

#include "FileUtils.h"
#include <stdio.h>
#include <stdlib.h>


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

void FileUtils::ReadColliderFile(std::string absolutePathToFile, glm::vec3& position, glm::vec3& scale, glm::vec3& rotation)
{
	if (!IsFileThere(absolutePathToFile))
	{
		Logger::LogError("File", absolutePathToFile, "not found!!");
		return;
	}
	char buf[512];
	FILE* f;
	f = fopen(absolutePathToFile.c_str(), "r");

	if (f != NULL)
	{
		while (!feof(f))
		{

		char c = fgetc(f);

		if (c == 'P')
		{
			float x, y, z;
			fscanf(f,"%f %f %f", &x, &y, &z);
			position.x = x;
			position.y = y;
			position.z = z;
		}
		else if (c == 'S')
		{
			float x, y, z;
			fscanf(f, "%f %f %f", &x, &y, &z);
			scale.x = x;
			scale.y = y;
			scale.z = z;
		}
		else if (c == 'R')
		{
			float x, y, z;
			fscanf(f, "%f %f %f", &x, &y, &z);
			rotation.x = x;
			rotation.y = y;
			rotation.z = z;
		}

		fgets(buf, 512, f);
		}
	}
}
