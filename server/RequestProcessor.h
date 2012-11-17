#pragma once

#include "..\ProtocolSpecification.h"
#include "ViewsCollection.h"
#include "ObjectsContainer.h"

class RequestProcessor
{
public:
	~RequestProcessor(void);

	static RequestProcessor* instance();

	int mainLoopIteration(); //�������� ���� ������ �������
protected:
	RequestProcessor();
private:
	static RequestProcessor* _instance;
	typedef ObjectsContainer* (*viewFunction) (char*, char*);

	void displatchRequest(RequestHeader *header, char* body); //�������� ��������������� �������������
	void responseDecorator(viewFunction view, RequestHeader *header, char* body); //���������� ������������� � ��������� ����� �������
	void sendResponse(ResponseHeader *header, char* body); //���������� ����� �������

	int listening_socket;
	int working_socket;

	struct sockaddr_in client_address;
};

