#pragma once

#include "DatabaseObject.h"

class Asset : public DatabaseObject
{
public:
	Asset();
	Asset(char);
	~Asset();

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