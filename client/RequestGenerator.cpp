#include "StdAfx.h"
#include "RequestGenerator.h"

RequestGenerator::RequestGenerator(void)
{
}

RequestGenerator::~RequestGenerator(void)
{
}

RequestGenerator* RequestGenerator::_instance = 0;

RequestGenerator* RequestGenerator::instance()
{
	if (_instance == 0)
	{
		_instance = new RequestGenerator();
	}
	return _instance;
}
