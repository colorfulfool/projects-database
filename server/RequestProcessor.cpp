#include "RequestProcessor.h"
#include <string.h>
#include <cppconn\exception.h>
using namespace std;

#define PORT 1234

RequestProcessor::RequestProcessor(void)
{
	struct sockaddr_in server_address;

	listening_socket = socket(AF_INET, SOCK_STREAM, 0); //������ �����

	memset(&server_address, 0, sizeof(struct sockaddr_in));
	server_address.sin_family = AF_INET; //IPv4
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = inet_addr("0.0.0.0");

	bind(listening_socket, (struct sockaddr *)&server_address, sizeof(server_address));

	listen(listening_socket, SOMAXCONN);
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

	if (strcmp(usecase, "projects/")==0) responseDecorator(ViewsCollection::allProjects, header, body);
}

void RequestProcessor::responseDecorator(viewFunction view, RequestHeader *header, char* body)
{
	std::vector<DatabaseObject> *responseBody;
	ResponseHeader *response = new ResponseHeader();
	strcpy(response->URI, header->URI);

	try
	{
		responseBody = view(header->method, body);

		strcpy(response->status, "OK");
		response->bodySize = sizeof(responseBody->data());

		sendResponse(response, (char*)responseBody->data());
	} catch (sql::SQLException &error) {
		strcpy(response->status, "FAIL");
		response->bodySize = strlen(error.what());

		sendResponse(response, (char*)error.what());
	}
}

void RequestProcessor::sendResponse(ResponseHeader *header, char* body)
{
	printf("%s %s\n", header->URI, header->status);

	send(working_socket, (char*)header, sizeof(ResponseHeader), NULL);
	send(working_socket, (char*)body, header->bodySize, NULL);
}

int RequestProcessor::mainLoopIteration()
{
	int size_of_address = sizeof(struct sockaddr_in);
	working_socket = accept(listening_socket, (struct sockaddr *)&client_address, &size_of_address);

	printf("Client %s\n connected.", inet_ntoa(client_address.sin_addr));

	//��� ����� ��������
	while (1)
	{
		RequestHeader *header = new RequestHeader();
		if (recv(working_socket, (char*)header, sizeof(RequestHeader), NULL) > 0) //�������� ���������
		{
			char *body = (char*)malloc(header->bodySize);
			recv(working_socket, body, header->bodySize, NULL); //�������� ���� �������

			displatchRequest(header, body);
		} else {
			break;
		}
	}
}