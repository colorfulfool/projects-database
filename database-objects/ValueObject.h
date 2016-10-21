#pragma once

#include "DatabaseObject.h"

class ValueObject : public DatabaseObject
{
public:
	ValueObject();
	ValueObject(char);
	~ValueObject();

	WCHAR name[100];
	WCHAR value[100];

	// void fillFromData(sql::ResultSet *data);
	virtual DatabaseObject* createSameObject();
	virtual int sizeOfSelf();

	// virtual LPWSTR getUpdateSQL();
	// virtual LPWSTR getDeleteSQL();
	// virtual LPWSTR getSelectObjectSQL();
private:
	
};