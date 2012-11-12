#include "DatabaseObject.h"

DatabaseObject::DatabaseObject()
{
}

DatabaseObject::~DatabaseObject()
{

}

LPWSTR DatabaseObject::getUpdateSQL()
{
	return L"Not implemented";
}

LPWSTR DatabaseObject::getDeleteSQL()
{
	return L"Not implemented";
}

void DatabaseObject::fillFromData(sql::ResultSet *data)
{

}

DatabaseObject* DatabaseObject::createSameObject()
{
	return NULL;
}