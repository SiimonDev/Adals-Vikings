#pragma once
#include <vector>
class Item;

namespace ObjectID{
	enum ObjID{
		NONE,
		Rock
	};
}


class ObjectHandler
{
public:
	static ObjectHandler &getInstance();
	~ObjectHandler();
	std::vector<Item*>& getItems();
	void initialize();

private:
	ObjectHandler();
	ObjectHandler(const ObjectHandler &objHandler);
	void operator=(const ObjectHandler &objHandler);
	std::vector<Item*> items;
};

