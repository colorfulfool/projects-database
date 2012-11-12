#include "ViewsCollection.h"

ViewsCollection::ViewsCollection(void)
{
}

ViewsCollection::~ViewsCollection(void)
{
}

ViewsCollection* ViewsCollection::_instance = 0;

ViewsCollection* ViewsCollection::instance()
{
	if (_instance == 0)
	{
		_instance = new ViewsCollection();
	}
	return _instance;
}

std::vector<DatabaseObject>* ViewsCollection::allProjects(char* method, char* requestBody)
{
	return 0;
}
