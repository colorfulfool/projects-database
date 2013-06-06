#include "RequestProcessor.h"
#include <string.h>
#include <cppconn\exception.h>
using namespace std;

RequestProcessor::RequestProcessor(int socket_to_use)
{
	this->working_socket = socket_to_use;
}

RequestProcessor::~RequestProcessor(void)
{
}

void RequestProcessor::displatchRequest(RequestHeader *header, char* body)
{
	char* usecase = header->URI;
	
	printf("%s %s -> ", header->method, header->URI);

	if (strcmp(usecase, "/sale")==0) responseDecorator(ViewsCollection::allSales, header, body); //перебираю представления в поисках подходящего
	if (strcmp(usecase, "/sale/product")==0) responseDecorator(ViewsCollection::productSales, header, body);
	if (strcmp(usecase, "/purchase/product")==0) responseDecorator(ViewsCollection::productPurchases, header, body);
	if (strcmp(usecase, "/profitabitily")==0) responseDecorator(ViewsCollection::allProfitability, header, body);
	if (strcmp(usecase, "/profitabitily/product")==0) responseDecorator(ViewsCollection::productProfitability, header, body);
}

void RequestProcessor::responseDecorator(viewFunction view, RequestHeader *header, char* body)
{
	ObjectsContainer *responseBody;
	ResponseHeader *response = new ResponseHeader();
	strcpy(response->URI, header->URI);

	try
	{
		responseBody = view(header->method, body);

		if (strcmp((char*)responseBody, "FAIL")==0)
		{
			char *msg = (char*)responseBody + 5;
			std::string *messagePacked = new std::string(msg);
			throw sql::SQLException(*messagePacked);
		}

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
	printf("%s %s (%d)\n", header->URI, header->status, working_socket);

	send(working_socket, (char*)header, sizeof(ResponseHeader), NULL);

	if (header->bodySize > 0) //нужно отправить еще и тело
		send(working_socket, (char*)body, header->bodySize, NULL);
}

int RequestProcessor::mainLoopIteration()
{
	while (1)
	{
		RequestHeader *header = new RequestHeader();
		if (recv(working_socket, (char*)header, sizeof(RequestHeader), NULL) >= 0) //принимаю заголовок
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
