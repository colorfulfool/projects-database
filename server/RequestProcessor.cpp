#include "RequestProcessor.h"
#include <string.h>
#include <cppconn\exception.h>
using namespace std;



#define PORT 1234

RequestProcessor::RequestProcessor(void)
{
	struct sockaddr_in server_address;

	listening_socket = socket(AF_INET, SOCK_STREAM, 0); //создаю сокет

	memset(&server_address, 0, sizeof(struct sockaddr_in));
	server_address.sin_family = AF_INET; //IPv4
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = inet_addr("0.0.0.0");

	bind(listening_socket, (struct sockaddr *)&server_address, sizeof(server_address));

	listen(listening_socket, SOMAXCONN);

	printf("Serving requests at %s:%d...\n", inet_ntoa(server_address.sin_addr), PORT);
}

RequestProcessor::~RequestProcessor(void)
{
}

RequestProcessor* RequestProcessor::_instance = 0;

RequestProcessor* RequestProcessor::instance()
{
	if (_instance == 0)
	{
		_instance = new RequestProcessor();
	}
	return _instance;
}

void RequestProcessor::displatchRequest(RequestHeader *header, char* body)
{
	char* usecase = header->URI;
	
	printf("%s %s -> ", header->method, header->URI);

	if (strcmp(usecase, "/project")==0) responseDecorator(ViewsCollection::allProjects, header, body); //перебираю представления в поисках подходящего
	if (strcmp(usecase, "/project/lecturer")==0) responseDecorator(ViewsCollection::lecturerProjects, header, body);
	if (strcmp(usecase, "/project/group")==0) responseDecorator(ViewsCollection::groupProjects, header, body);
	if (strcmp(usecase, "/lecturer")==0) responseDecorator(ViewsCollection::allLecturers, header, body);
	if (strcmp(usecase, "/student")==0) responseDecorator(ViewsCollection::allStudents, header, body);
}

void RequestProcessor::responseDecorator(viewFunction view, RequestHeader *header, char* body)
{
	ObjectsContainer *responseBody;
	ResponseHeader *response = new ResponseHeader();
	strcpy(response->URI, header->URI);

	try
	{
		responseBody = view(header->method, body);

		strcpy(response->status, "OK");

		if (responseBody != NULL) //сервер что-то возвращает
		{
			response->bodySize = responseBody->totalSize();
			sendResponse(response, responseBody->dataPointer());
		} else { //сервер не возвращает ничего (значит, и не надо)
			response->bodySize = 0;
			sendResponse(response, NULL);
		}
	} catch (sql::SQLException &error) {
		strcpy(response->status, "FAIL");
		response->bodySize = strlen(error.what())+1;

		sendResponse(response, (char*)error.what());
	}
}

void RequestProcessor::sendResponse(ResponseHeader *header, char* body)
{
	printf("%s %s\n", header->URI, header->status);

	send(working_socket, (char*)header, sizeof(ResponseHeader), NULL);

	if (header->bodySize > 0) //нужно отправить еще и тело
		send(working_socket, (char*)body, header->bodySize, NULL);
}

int RequestProcessor::mainLoopIteration()
{
	int size_of_address = sizeof(struct sockaddr_in);
	working_socket = accept(listening_socket, (struct sockaddr *)&client_address, &size_of_address);

	printf("Client %s connected.\n", inet_ntoa(client_address.sin_addr));

	//тут можно форкнуть
	while (1)
	{
		RequestHeader *header = new RequestHeader();
		if (recv(working_socket, (char*)header, sizeof(RequestHeader), NULL) > 0) //принимаю заголовок
		{
			char *body;
			if (header->bodySize > 0)
			{
				body = (char*)malloc(header->bodySize);
				recv(working_socket, body, header->bodySize, NULL); //принимаю тело запроса
			} else {
				body = 0;
			}

			displatchRequest(header, body);
		} else {
			break;
		}
	}

	return 0;
}