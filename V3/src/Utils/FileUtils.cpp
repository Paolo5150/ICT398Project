#include "pch.h"

#include "FileUtils.h"


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