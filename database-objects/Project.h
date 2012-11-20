#pragma once

#include "DatabaseObject.h"

class Project : public DatabaseObject
{
public:
	Project();
	Project(char);
	~Project();

	WCHAR task[100];
	WCHAR subject[50];
	WCHAR dueTo[50];
	int completeness;

	WCHAR lecturer[100];
	int lecturer_id;
	WCHAR student[100];
	int student_id;

	void fillFromData(sql::ResultSet *data);
	virtual DatabaseObject* createSameObject();
	virtual int sizeOfSelf();

	virtual LPWSTR getUpdateSQL();
	virtual LPWSTR getDeleteSQL();
	virtual LPWSTR getSelectObjectSQL();
private:
	
};