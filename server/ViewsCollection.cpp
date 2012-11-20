#include "ViewsCollection.h"
#include "DatabaseWrapper.h"
#include "Project.h"
#include "Student.h"
#include "Lecturer.h"

#include <cppconn\exception.h>

ViewsCollection::ViewsCollection(void)
{
}

ViewsCollection::~ViewsCollection(void)
{
}

ObjectsContainer* ViewsCollection::allProjects(char* method, char* requestBody)
{
	if (strcmp(method, "GET") == 0) //GET - ������ �������
		return DatabaseWrapper::instance()->getObjects(new Project());
	if ((strcmp(method, "PUT") == 0)||(strcmp(method, "POST") == 0)) //PUT ��� POST - ������ ����������
	{
		Project *object = (Project*)requestBody;

		ObjectsContainer *result; //���������� � �������� �������:
		result = DatabaseWrapper::instance()->getObjectsByAttribute(new Lecturer(), L"name", object->lecturer); //�� ������� �� �������������
		if (result->next() == FALSE) throwAnException("Foreign key error: no such lecturer"); //�� ��������� �� ������ ������� - ���-�� ����� �� ���, ������ ����������
		object->lecturer_id = result->current()->id;

		result = DatabaseWrapper::instance()->getObjectsByAttribute(new Student(), L"name", object->student); //� �� ��������
		if (result->next() == FALSE) throwAnException("Foreign key error: no such student");
		object->student_id = result->current()->id;

		DatabaseWrapper::instance()->updateObject(object);
		return NULL;
	}
	if (strcmp(method, "DELETE") == 0) //DELETE - ������ ��������
	{
		DatabaseWrapper::instance()->deleteObject(new Project(*(Project*)requestBody));
		return NULL;
	}
}

ObjectsContainer* ViewsCollection::groupProjects(char method[6], char* requestBody)
{
	return DatabaseWrapper::instance()->getObjectsByAttribute(new Project(), L"student_group", (LPCWSTR)requestBody);
}

ObjectsContainer* ViewsCollection::lecturerProjects(char method[6], char* requestBody)
{
	return DatabaseWrapper::instance()->getObjectsByAttribute(new Project(), L"lecturer", (LPCWSTR)requestBody);
}

ObjectsContainer* ViewsCollection::allStudents(char method[6], char* requestBody)
{
	if (strcmp(method, "GET") == 0)
		return DatabaseWrapper::instance()->getObjects(new Student());
	if (strcmp(method, "PUT") == 0)
	{
		DatabaseWrapper::instance()->updateObject((Student*)requestBody);
		return NULL;
	}
	if (strcmp(method, "POST") == 0)
	{
		DatabaseWrapper::instance()->updateObject((Student*)requestBody);
		return NULL;
	}
	if (strcmp(method, "DELETE") == 0)
	{
		DatabaseWrapper::instance()->deleteObject((Student*)requestBody);
		return NULL;
	}
}

ObjectsContainer* ViewsCollection::allLecturers(char method[6], char* requestBody)
{
	if (strcmp(method, "GET") == 0)
		return DatabaseWrapper::instance()->getObjects(new Lecturer());
	if (strcmp(method, "PUT") == 0)
	{
		DatabaseWrapper::instance()->updateObject((Lecturer*)requestBody);
		return NULL;
	}
	if (strcmp(method, "POST") == 0)
	{
		DatabaseWrapper::instance()->updateObject((Lecturer*)requestBody);
		return NULL;
	}
	if (strcmp(method, "DELETE") == 0)
	{
		DatabaseWrapper::instance()->deleteObject((Lecturer*)requestBody);
		return NULL;
	}
}

void ViewsCollection::throwAnException(char* message)
{
	std::string *messagePacked = new std::string(message);
	throw sql::SQLException(*messagePacked);
}