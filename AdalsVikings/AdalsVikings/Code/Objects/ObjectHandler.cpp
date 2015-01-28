#include "ObjectHandler.h"

ObjectHandler::ObjectHandler()
{
	
}

ObjectHandler::~ObjectHandler()
{

}

ObjectHandler &ObjectHandler::getInstance()
{
	static ObjectHandler instance;
	return instance;
}

std::vector<Item*>& ObjectHandler::getItems(){
	
	return items;
}

void ObjectHandler::initialize(){
	//Create all items from the text file here
}