#pragma once

#include "DatabaseObject.h"

class DatabaseWrapper
{
public:
	~DatabaseWrapper(void);

	static DatabaseWrapper* instance();

	RET getObjects(DatabaseObject *object); //��������� ��� ������� ���������� ����
	RET getObjectsByAttribute(DatabaseObject *object, LPCWSTR attribute, LPCWSTR value); //��������� ������� ���������� ����, ������� ��������� �������� ��������
protected:
	DatabaseWrapper(void);
private:
	static DatabaseWrapper* _instance;
};

