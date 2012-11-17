#include "ViewsCollection.h"
#include "DatabaseWrapper.h"
#include "Project.h"

ViewsCollection::ViewsCollection(void)
{
}

ViewsCollection::~ViewsCollection(void)
{
}

ObjectsContainer* ViewsCollection::allProjects(char* method, char* requestBody)
{
	return DatabaseWrapper::instance()->getObjects(new Project());
}

ObjectsContainer* ViewsCollection::groupProjects(char method[6], char* requestBody)
{
	return DatabaseWrapper::instance()->getObjectsByAttribute(new Project(), L"lecturer", (LPCWSTR)requestBody);
}

ObjectsContainer* ViewsCollection::lecturerProjects(char method[6], char* requestBody)
{
	return DatabaseWrapper::instance()->getObjectsByAttribute(new Project(), L"student_group", (LPCWSTR)requestBody);
}
