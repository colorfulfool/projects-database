#pragma once
#include <vector>
#include "../database-objects/DatabaseObject.h"

class ViewsCollection
{
public:
	~ViewsCollection(void);

	static ViewsCollection* instance();

	static std::vector<DatabaseObject>* allProjects(char method[6], char* requestBody);
protected:
	ViewsCollection(void);
private:
	static ViewsCollection* _instance;
};

