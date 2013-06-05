#include "RequestGenerator.h"
#include "DatabaseObject.h"
#include "Project.h"
#include "ObjectsContainer.h"
#include "Lecturer.h"
#include "Student.h"

RequestGenerator::RequestGenerator(void)
{
	socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_id == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		mainForm->MessageBox(L"Не удалось создать сокет.");
	}
}

int RequestGenerator::connectToServer(char *address, int port)
{
	memset(&server_address, 0, sizeof(struct sockaddr_in));
	server_address.sin_family = AF_INET; //IPv4
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = inet_addr(address);

	int returned = connect(socket_id, (const sockaddr*)&server_address, sizeof(struct sockaddr_in));
	if (returned != 0)
	{
		mainForm->MessageBox(L"Не удалось подключиться.");
	}

	return returned;
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

ResponseBody RequestGenerator::sendRequest(char method[4], char URI[50], char* body, int bodySize)
{
	RequestHeader *header = new RequestHeader; //заголовок запроса

	strcpy(header->method, method);
	strcpy(header->URI, URI);
	header->bodySize = bodySize;

	send(socket_id, (char*)header, sizeof(RequestHeader), NULL);
	send(socket_id, body, bodySize, NULL);

	//тем временем сервер обраротал запрос

	ResponseHeader *response = new ResponseHeader;
	recv(socket_id, (char*)response, sizeof(RequestHeader), NULL); //принимаю заголовок ответа

	char *responseBody = (char*)malloc(response->bodySize);
	if (response->bodySize > 0)
		recv(socket_id, (char*)responseBody, response->bodySize, NULL);

	ResponseBody resp;
	if (strcmp(response->status, "OK") == 0)
	{
		resp.body = responseBody;
		resp.size = response->bodySize;

		return resp;
	} else if (strcmp(response->status, "FAIL") == 0) //если произошла ошибка
	{
		WCHAR *messageEncoded = (WCHAR*)calloc(response->bodySize, sizeof(WCHAR));
		mbstowcs(messageEncoded, responseBody, response->bodySize);
		mainForm->showError(messageEncoded); //показываю сообщение об этом
		
		resp.size = 0;
		return resp; //нуждается а проверке
	} else {
		mainForm->showError(L"Непонятный ответ сервера.");
		
		resp.size = 0;
		return resp;
	}
}

void RequestGenerator::groupProjects(LPCWSTR groupName)
{
	ResponseBody result = sendRequest("GET", "/project/group", (char*)groupName, (wcslen(groupName)+1)*sizeof(WCHAR));

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayProjects(objects);
	}
}

void RequestGenerator::lecturerProjects(LPCWSTR lenctuerName)
{
	ResponseBody result = sendRequest("GET", "/project/lecturer", (char*)lenctuerName, (wcslen(lenctuerName)+1)*sizeof(WCHAR));

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayProjects(objects);
	}
}

void RequestGenerator::allProjects()
{
	ResponseBody result = sendRequest("GET", "/project", NULL, 0);

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayProjects(objects);
	}
}

void RequestGenerator::addProject(LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student)
{
	Project *newOne = new Project(); //добавляемый в базу курсовой

	wcscpy(newOne->task, task);
	wcscpy(newOne->subject, subject);
	wcscpy(newOne->dueTo, dueTo);
	newOne->completeness = completeness;
	wcscpy(newOne->lecturer, lecturer);
	wcscpy(newOne->student, student);

	sendRequest("POST", "/project", (char*)newOne, sizeof(Project));
}

void RequestGenerator::addLecturer(LPCWSTR fullName)
{
	Lecturer *newOne = new Lecturer();

	wcscpy(newOne->name, fullName);

	sendRequest("POST", "/lecturer", (char*)newOne, sizeof(Lecturer));
}

void RequestGenerator::addStudent(LPCWSTR fullName, LPCWSTR group)
{
	Student *newOne = new Student();

	wcscpy(newOne->name, fullName);
	wcscpy(newOne->group, group);

	sendRequest("POST", "/student", (char*)newOne, sizeof(Student));
}

void RequestGenerator::editProject(int id, LPCWSTR task, LPCWSTR subject, LPCWSTR dueTo, int completeness, LPCWSTR lecturer, LPCWSTR student)
{
	Project *newOne = new Project();

	newOne->id = id;
	wcscpy(newOne->task, task);
	wcscpy(newOne->subject, subject);
	wcscpy(newOne->dueTo, dueTo);
	newOne->completeness = completeness;
	wcscpy(newOne->lecturer, lecturer);
	wcscpy(newOne->student, student);

	sendRequest("PUT", "/project", (char*)newOne, sizeof(Project));
}

void RequestGenerator::removeProject(int id)
{
	Project *newOne = new Project();

	newOne->id = id;

	sendRequest("DELETE", "/project", (char*)newOne, sizeof(Project));
}

void RequestGenerator::setMainForm(CclientDlg *dialog)
{
	mainForm = dialog;
}

void RequestGenerator::diagram(LPCWSTR groupName)
{
	ResponseBody result = sendRequest("GET", "/project/group", (char*)groupName, (wcslen(groupName)+1)*sizeof(WCHAR));

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayDiagram(objects);
	}
}

void RequestGenerator::fullReport()
{
	ResponseBody result = sendRequest("GET", "/project", NULL, 0);

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->saveTextReport(objects);
	}
}