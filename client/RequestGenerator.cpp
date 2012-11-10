#include "StdAfx.h"
#include "RequestGenerator.h"

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

void sendRequest(char method[4], char URI[50], char* body, int bodySize)
{

}

void groupProjects(LPCWSTR groupName)
{
	sendRequest("GET", "/projects/group", (char*)groupName, sizeof(groupName));
}

void lecturerProjects(LPCWSTR lenctuerName)
{
	sendRequest("GET", "/projects/lecturer", (char*)lenctuerName, sizeof(lenctuerName));
}

void allProjects()
{
	sendRequest("GET", "/projects", NULL, 0);
}

void addProject(LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student)
{

}

void addLecturer(LPCWSTR fullName)
{

}

void addStudent(LPCWSTR fullName, LPCWSTR group)
{

}

void editProject(LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student)
{

}

void removeProject(int id)
{

}

