#include "Level.h"
#include <iostream>
#include <vector>
#include <string>


Level::Level()
{
}


Level::~Level()
{
}

void Level::readFiles(std::string directory)
{
	DIR *dir;
	std::vector<std::string> filePaths;

	struct dirent *dirnt;

	if ((dir = opendir(directory.c_str())) != NULL)
	{
		while ((dirnt = readdir(dir)) != NULL)
		{
			filePaths.push_back(dirnt->d_name);
		}
		closedir(dir);

		for each (std::string s in filePaths)
		{
			std::cout << s << std::endl;
		}
	}
	else {
		/* could not open directory */
		std::cout << "Could not find dir" << std::endl;
	}
}
