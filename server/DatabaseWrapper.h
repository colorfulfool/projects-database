#pragma once

#include "DatabaseObject.h"

class DatabaseWrapper
{
public:
	~DatabaseWrapper(void);

	static DatabaseWrapper* instance();

	RET getObjects(DatabaseObject *object); //возващает все объекты указанного типа
	RET getObjectsByAttribute(DatabaseObject *object, LPCWSTR attribute, LPCWSTR value); //возращает объекты указанного типа, имеющие указанное значение атрибута
protected:
	DatabaseWrapper(void);
private:
	static DatabaseWrapper* _instance;
};

