#pragma once

#include <Windows.h>
#include <C:\Program Files\MySQL\MySQL Connector C++ 1.1.1\include\cppconn\resultset.h>
//#include "DatabaseWrapper.h"

class DatabaseObject //������������ ������ �� ���� ������ � ���� �������
{
public:
	DatabaseObject();
	~DatabaseObject();

	virtual void fillFromData(sql::ResultSet *data); //��������� ���� ������� �� ������ ������ �� ����
	virtual LPWSTR getUpdateSQL(); //���������� SQL-������, ����������� ������ � ����
	virtual LPWSTR getDeleteSQL();
	virtual LPWSTR getSelectObjectSQL();
	
	virtual LPWSTR getRelatedByNameSQL(LPCWSTR name);

	virtual DatabaseObject* createSameObject(); //��������� �����, ���������� ������ ���� �� ����
	virtual int sizeOfSelf(); //���������� ������ ������� ������ ������

	int id; //��������� ���� ������� � ��� �������
	char table[50]; //�������� �������
private:
	
};