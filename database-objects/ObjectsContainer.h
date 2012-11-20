#pragma once

#include "DatabaseObject.h"

class ObjectsContainer //���������/��������, ������ �������� DatabaseObject, �� ���� �� ����������� ������
{
public:
	ObjectsContainer(void);
	ObjectsContainer(DatabaseObject *example, int count); //��������� �������� ���������� � ������ �������� ��������
	~ObjectsContainer(void);

	void append(DatabaseObject *object);
	int totalSize(); //����� ������ ��������� (�� ���� ���� ��������)

	char* dataPointer(); //���������� ��������� �� ���������
	
	void setDataPointer(char* pointer);
	bool next();
	DatabaseObject* current();

private:
	char* storage;
	int objectSize;
	int objectsCount;

	int currentIndex;
};

