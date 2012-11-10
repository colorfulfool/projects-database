#include "RequestProcessor.h"

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
