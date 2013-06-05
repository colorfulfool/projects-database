#pragma once
#include <vector>
#include "../database-objects/DatabaseObject.h"
#include "ObjectsContainer.h"

class ViewsCollection
{
public:
	~ViewsCollection(void);

	static ObjectsContainer* allProjects(char method[6], char* requestBody); //����� ��� �������� ��� ��������� (�������, ����������, etc)
	static ObjectsContainer* groupProjects(char method[6], char* requestBody);
	static ObjectsContainer* lecturerProjects(char method[6], char* requestBody);

	static ObjectsContainer* allStudents(char method[6], char* requestBody); //��� �������� ��� ����������
	static ObjectsContainer* allLecturers(char method[6], char* requestBody);

	static ObjectsContainer* throwAnException(char* message);
protected:
	ViewsCollection(void);
private:
	
};

