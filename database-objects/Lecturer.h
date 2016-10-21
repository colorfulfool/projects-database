#pragma once

#include "DatabaseObject.h"

class Lecturer : public DatabaseObject
{
public:
	Lecturer();
	Lecturer(char);
	~Lecturer();

	WCHAR name[100];

	void fillFromData(sql::ResultSet *data);
	virtual DatabaseObject* createSameObject();
	virtual int sizeOfSelf();

	virtual LPWSTR getUpdateSQL();
	virtual LPWSTR getDeleteSQL();
	virtual LPWSTR getSelectObjectSQL();
private:
	
};