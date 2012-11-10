#include "DatabaseWrapper.h"

DatabaseWrapper::DatabaseWrapper(void)
{
}

DatabaseWrapper::~DatabaseWrapper(void)
{
}

DatabaseWrapper* DatabaseWrapper::_instance = 0;

DatabaseWrapper* DatabaseWrapper::instance()
{
	if (_instance == 0)
	{
		_instance = new DatabaseWrapper();
	}
	return _instance;
}
