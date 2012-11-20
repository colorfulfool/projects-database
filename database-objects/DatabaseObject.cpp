#include "DatabaseObject.h"

DatabaseObject::DatabaseObject()
{
	this->id = 0;
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

int DatabaseObject::sizeOfSelf()
{
	return sizeof(DatabaseObject);
}

LPWSTR DatabaseObject::getSelectObjectSQL()
{
	return L"Not implemented";
}