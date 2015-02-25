#include "ObjectHandler.h"
#include "Object.h"
#include <External\dirent.h>
#include <iostream>
#include <fstream>

ObjectHandler::ObjectHandler()
{
	mFolderPath = "Assets/objects/";
}

ObjectHandler &ObjectHandler::getInstance()
{
	static std::unique_ptr<ObjectHandler> instance;

	if (instance == NULL)
		instance = std::unique_ptr<ObjectHandler>(new ObjectHandler());

	return *instance;
}

Object &ObjectHandler::getObject(std::string objID)
{	
	return *mObjects.at(objID);
}

std::vector<std::string> getAllObjectsFromFolder(const std::string &directory)
{
	DIR *dir;
	struct dirent *dirnt;
	std::vector<std::string> filePaths;

	if ((dir = opendir(directory.c_str())) != NULL)
	{
		while ((dirnt = readdir(dir)) != NULL)
		{
			std::string path = dirnt->d_name;
			if (path.find("obj_") != std::string::npos){
				filePaths.push_back(directory + dirnt->d_name);
			}
		}
		closedir(dir);
	}
	else{
		//std::cout << "Could not find dir" << std::endl;
	}

	return filePaths;
}

void ObjectHandler::initialize()
{
	std::vector<std::string> objects = getAllObjectsFromFolder(mFolderPath);

	for each (std::string file in objects)
	{
		Object* obj = new Object(file, mFolderPath);
		mObjects[obj->getObjID()] = obj;
	}
}

void ObjectHandler::unload()
{
	for (std::map<std::string, Object*>::const_iterator it = mObjects.begin(); it != mObjects.end(); it++)
	{
		it->second->unload();
	}
	mObjects.clear();

}
