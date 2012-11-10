#pragma once

#include "..\ProtocolSpecification.h"

class RequestProcessor
{
public:
	~RequestProcessor(void);

	static RequestProcessor* instance();
protected:
	RequestProcessor();
private:
	static RequestProcessor* _instance;
};

