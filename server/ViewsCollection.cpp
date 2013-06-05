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
	if (strcmp(method, "GET") == 0) //GET - значит выборка
		return DatabaseWrapper::instance()->getObjects(new Project());
	if ((strcmp(method, "PUT") == 0)||(strcmp(method, "POST") == 0)) //PUT или POST - значит обновление
	{
		Project *object = new Project(*(Project*)requestBody);

		ObjectsContainer *result; //разбираюсь с внешними ключами:
		result = DatabaseWrapper::instance()->getObjectsByAttribute(new Lecturer(), L"name", object->lecturer); //со ссылкой на преподавателя
		if (result->next() == FALSE)
			return throwAnException("Foreign key error: no such lecturer"); //не вернулось ни одного объекта - что-то пошло не так, бросаю исключение
		Lecturer* related_object = (Lecturer*)(result->current());
		object->lecturer_id = related_object->id;

		result = DatabaseWrapper::instance()->getObjectsByAttribute(new Student(), L"name", object->student); //и на студента
		if (result->next() == FALSE) 
			return throwAnException("Foreign key error: no such student");
		Student* another_related_object = (Student*)(result->current());
		object->student_id = another_related_object->id;

		DatabaseWrapper::instance()->updateObject(object);
		return NULL;
	}
	if (strcmp(method, "DELETE") == 0) //DELETE - значит удаление
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
		DatabaseWrapper::instance()->updateObject(new Student(*(Student*)requestBody));
		return NULL;
	}
	if (strcmp(method, "POST") == 0)
	{
		DatabaseWrapper::instance()->updateObject(new Student(*(Student*)requestBody));
		return NULL;
	}
	if (strcmp(method, "DELETE") == 0)
	{
		DatabaseWrapper::instance()->deleteObject(new Student(*(Student*)requestBody));
		return NULL;
	}
}

ObjectsContainer* ViewsCollection::allLecturers(char method[6], char* requestBody)
{
	if (strcmp(method, "GET") == 0)
		return DatabaseWrapper::instance()->getObjects(new Lecturer());
	if (strcmp(method, "PUT") == 0)
	{
		DatabaseWrapper::instance()->updateObject(new Lecturer(*(Lecturer*)requestBody));
		return NULL;
	}
	if (strcmp(method, "POST") == 0)
	{
		DatabaseWrapper::instance()->updateObject(new Lecturer(*(Lecturer*)requestBody));
		return NULL;
	}
	if (strcmp(method, "DELETE") == 0)
	{
		DatabaseWrapper::instance()->deleteObject(new Lecturer(*(Lecturer*)requestBody));
		return NULL;
	}
}

ObjectsContainer* ViewsCollection::throwAnException(char* message)
{
	//std::string *messagePacked = new std::string(message);
	//throw sql::SQLException(*messagePacked);

	char msgString[300] = "FAIL";
	strcpy(msgString+5, message);

	return (ObjectsContainer*)msgString;
}