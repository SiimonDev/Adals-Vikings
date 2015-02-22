#pragma once
#include "Object.h"
#include <memory>
#include <vector>
#include <map>

#define OBHI ObjectHandler::getInstance()

typedef std::unique_ptr<Object> ObjectPtr;

class ObjectHandler
{
public:
	static ObjectHandler &getInstance();
	void initialize();

	Object &getObject(std::string objID);

private:
	ObjectHandler();
	ObjectHandler(const ObjectHandler &objHandler);
	void operator=(const ObjectHandler &objHandler);

	std::string mFolderPath;

	std::map<std::string, Object*> mObjects;
};