#pragma once
#include <stdlib.h>
#include <string>
//#include <windows.h>
#include "clientDlg.h"

#include "..\ProtocolSpecification.h"

class CclientDlg;

struct ResponseBody //содержит тело ответа и размер этого тела
{
	int size;
	char *body;
};

class RequestGenerator
{
public:
	~RequestGenerator(void);

	static RequestGenerator* instance();

	int connectToServer(char *address, int port);
	ResponseBody sendRequest(char method[4], char URI[50], char* body, int bodySize);

	void groupProjects(LPCWSTR groupName);
	void lecturerProjects(LPCWSTR lenctuerName);
	void allProjects();
	void addProject(LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student);
	void addLecturer(LPCWSTR fullName);
	void addStudent(LPCWSTR fullName, LPCWSTR group);
	void editProject(LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student);
	void removeProject(int id);
	void fullReport();
	void diagram(LPCWSTR groupName);

	void setMainForm(CclientDlg *dialog);
protected:
	RequestGenerator(void);
private:
	static RequestGenerator* _instance;

	int socket_id;
	sockaddr_in server_address;

	CclientDlg *mainForm;
};

