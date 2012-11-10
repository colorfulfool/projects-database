#pragma once

#include "..\ProtocolSpecification.h"

class RequestGenerator
{
public:
	~RequestGenerator(void);

	static RequestGenerator* instance();

	void sendRequest(char method[4], char URI[50], char* body, int bodySize);
protected:
	RequestGenerator(void);
private:
	static RequestGenerator* _instance;
};

