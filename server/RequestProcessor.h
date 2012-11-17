#pragma once

#include "..\ProtocolSpecification.h"
#include "ViewsCollection.h"
#include "ObjectsContainer.h"

class RequestProcessor
{
public:
	~RequestProcessor(void);

	static RequestProcessor* instance();

	int mainLoopIteration(); //основной цикл работы сервера
protected:
	RequestProcessor();
private:
	static RequestProcessor* _instance;
	typedef ObjectsContainer* (*viewFunction) (char*, char*);

	void displatchRequest(RequestHeader *header, char* body); //выбирает соответствующее представление
	void responseDecorator(viewFunction view, RequestHeader *header, char* body); //использует представдение и формирует ответ сервера
	void sendResponse(ResponseHeader *header, char* body); //отправляет ответ клиенту

	int listening_socket;
	int working_socket;

	struct sockaddr_in client_address;
};

