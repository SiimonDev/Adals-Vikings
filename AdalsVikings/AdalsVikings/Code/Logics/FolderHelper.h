#include <External/dirent.h>
#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>

/* ======== My own functions ========*/
void copyFile(const std::string &from, const std::string &to)
{
	std::ifstream f1(from, std::fstream::binary);
	std::ofstream f2(to, std::fstream::trunc | std::fstream::binary);
	f2 << f1.rdbuf();
}

inline bool fileExists(const std::string &name) {
	struct stat buffer;
	return (stat(name.c_str(), &buffer) == 0);
}
/* ==================================*/


//// Copy all the object files to a save path
//const char* PATH = "assets/MapFiles";
//DIR *dir = opendir(PATH);
//struct dirent *entry = readdir(dir);
//while (entry != NULL)
//{
//	if (entry->d_type == DT_DIR)
//	{
//		std::string entry(entry->d_name);
//		std::string folderPath = "assets/mapfiles/" + entry + "/";

//		if (fileExists(folderPath + "level_objects.txt"))
//			copyFile(folderPath + "level_objects.txt", "assets/saves/mapfiles/level_objects_" + entry + ".txt");
//	}
//	entry = readdir(dir);
//}
//closedir(dir);

//// Copy all the save object files to the mapfiles folder
//const char* PATH = "assets/saves/mapfiles/";
//DIR *dir = opendir(PATH);
//struct dirent *entry = readdir(dir);
//while (entry != NULL)
//{
//	std::string name(entry->d_name);
//	if (name.find("level_objects") != std::string::npos)
//	{
//		// Do STUFF HERE
//		std::string subString = name.substr(14, name.size() - 18);
//		std::string filePath = "assets/saves/mapfiles/level_objects_" + name + ".txt";

//		copyFile(filePath, "assets/mapfiles/" + subString + "/level_objects.txt");
//	}
//	entry = readdir(dir);
//}
//closedir(dir);