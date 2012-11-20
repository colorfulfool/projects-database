#pragma once

#include "DatabaseObject.h"

class Student : public DatabaseObject
{
public:
	Student();
	Student(char);
	~Student();

	WCHAR name[100];
	WCHAR group[50];

	void fillFromData(sql::ResultSet *data);
	virtual DatabaseObject* createSameObject();
	virtual int sizeOfSelf();

	virtual LPWSTR getUpdateSQL();
	virtual LPWSTR getDeleteSQL();
	virtual LPWSTR getSelectObjectSQL();
private:
	
};