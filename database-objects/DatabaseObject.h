#pragma once

#include <Windows.h>

class DatabaseObject //������������ ������ �� ���� ������ � ���� �������
{
public:
	DatabaseObject();
	~DatabaseObject();

	virtual LPWSTR getUpdateSQL(); //���������� SQL-������, ����������� ������ � ����
	virtual LPWSTR getDeleteSQL();

	int id; //��������� ���� ������� � ��� �������
	char table[50]; //�������� �������
private:
	
};