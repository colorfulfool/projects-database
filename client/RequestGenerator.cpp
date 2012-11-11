#include "RequestGenerator.h"
#include "DatabaseObject.h"
#include "Project.h"

RequestGenerator::RequestGenerator(void)
{
}

RequestGenerator::~RequestGenerator(void)
{
}

RequestGenerator* RequestGenerator::_instance = 0;

RequestGenerator* RequestGenerator::instance()
{
	if (_instance == 0)
	{
		_instance = new RequestGenerator();
	}
	return _instance;
}

void RequestGenerator::sendRequest(char method[4], char URI[50], char* body, int bodySize)
{
	RequestHeader header; //заголовок запроса

	strcpy(header.method, method);
	strcpy(header.URI, URI);
	header.bodySize = bodySize;

	printf("%s %s %d", header.method, header.URI, header.bodySize);
}

void RequestGenerator::groupProjects(LPCWSTR groupName)
{
	sendRequest("GET", "/project/group", (char*)groupName, sizeof(groupName));
}

void RequestGenerator::lecturerProjects(LPCWSTR lenctuerName)
{
	sendRequest("GET", "/project/lecturer", (char*)lenctuerName, sizeof(lenctuerName));
}

void RequestGenerator::allProjects()
{
	sendRequest("GET", "/project", NULL, 0);
}

void RequestGenerator::addProject(LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student)
{
	Project *newOne = new Project(); //добавляемый в базу курсовой

	wcscpy(newOne->task, task);
	wcscpy(newOne->subject, subject);
	wcscpy(newOne->dueTo, dueTo);
	newOne->completeness = completeness;
	wcscpy(newOne->lecturer, lecturer);

	sendRequest("POST", "/project", (char*)newOne, sizeof(Project));
}

void RequestGenerator::addLecturer(LPCWSTR fullName)
{

}

void RequestGenerator::addStudent(LPCWSTR fullName, LPCWSTR group)
{

}

void RequestGenerator::editProject(LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student)
{
	Project *newOne = new Project();

	wcscpy(newOne->task, task);
	wcscpy(newOne->subject, subject);
	wcscpy(newOne->dueTo, dueTo);
	newOne->completeness = completeness;
	wcscpy(newOne->lecturer, lecturer);

	sendRequest("PUT", "/project", (char*)newOne, sizeof(Project));
}

void RequestGenerator::removeProject(int id)
{
	sendRequest("DELETE", "/project", (char*)id, sizeof(int));
}

