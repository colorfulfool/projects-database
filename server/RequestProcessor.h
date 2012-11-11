#pragma once

#include "..\ProtocolSpecification.h"
#include "ViewsCollection.h"

class RequestProcessor
{
public:
	~RequestProcessor(void);

	static RequestProcessor* instance();
protected:
	RequestProcessor();
private:
	static RequestProcessor* _instance;
	typedef std::vector<DatabaseObject>* (*viewFunction) (char*, char*);

	void displatchRequest(RequestHeader *header, char* body); //�������� ��������������� �������������
	void responseDecorator(viewFunction view, RequestHeader *header, char* body); //���������� ������������� � ��������� ����� �������
	void sendResponse(ResponseHeader *header, char* body); //���������� ����� �������
};

