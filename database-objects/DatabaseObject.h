#pragma once

#include <Windows.h>

class DatabaseObject //������������ ������ �� ���� ������ � ���� �������
{
public:
	DatabaseObject();
	~DatabaseObject();

	virtual LPWSTR getUpdateSQL(); //���������� SQL-������, ����������� ������ � ����
	virtual LPWSTR getDeleteSQL();
private:
	int id; //��������� ���� ������� � ��� �������
};