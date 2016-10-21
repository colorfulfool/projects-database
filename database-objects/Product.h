#pragma once

#include "DatabaseObject.h"

class Product : public DatabaseObject
{
public:
	Product();
	Product(char);
	~Product();

	int id;
	WCHAR name[100];

	void fillFromData(sql::ResultSet *data);
	virtual DatabaseObject* createSameObject();
	virtual int sizeOfSelf();

	// virtual LPWSTR getUpdateSQL();
	// virtual LPWSTR getDeleteSQL();
	virtual LPWSTR getSelectObjectSQL();
private:
	
};