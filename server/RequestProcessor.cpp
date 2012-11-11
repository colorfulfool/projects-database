#include "RequestProcessor.h"
#include <string.h>

RequestProcessor::RequestProcessor(void)
{
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

	if (strcmp(usecase, "projects/")==0) responseDecorator(ViewsCollection::allProjects, header, body);

}

void RequestProcessor::responseDecorator(viewFunction view, RequestHeader *header, char* body)
{
	std::vector<DatabaseObject> *responseBody = view(header->method, body);
	ResponseHeader *response = new ResponseHeader();
	strcpy(response->URI, header->URI);

	if (responseBody != 0)
	{
		strcpy(response->status, "OK");
		response->bodySize = sizeof(responseBody->data());

		sendResponse(response, (char*)responseBody->data());
	} else {
		strcpy(response->status, "FAIL");
		response->bodySize = 0;

		sendResponse(response, 0);
	}
}

void RequestProcessor::sendResponse(ResponseHeader *header, char* body)
{

}