#pragma once
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn\driver.h>
#include <cppconn\statement.h>
#include <cppconn\resultset.h>
#include "sqlstring.h"
#include <vector>

#include "DatabaseObject.h"
#include "ObjectsContainer.h"

class DatabaseWrapper
{
public:
	~DatabaseWrapper(void);

	static DatabaseWrapper* instance();

	void connectToDatabase();
	void recreateDatabase(); //создает структуру базы данных

	ObjectsContainer* getObjects(DatabaseObject *object); //возвращает все объекты указанного типа
	ObjectsContainer* getRelatedObjects(DatabaseObject *object, LPCWSTR relatedName); //возвращает все объекты указанного типа
	ObjectsContainer* getObjectsByAttribute(DatabaseObject *object, LPCWSTR attribute, LPCWSTR value); //возращает объекты указанного типа, имеющие указанное значение атрибута
	void updateObject(DatabaseObject *object);
	void deleteObject(DatabaseObject *object);
protected:
	DatabaseWrapper(void);
private:
	static DatabaseWrapper* _instance;

	sql::Connection *con;
	sql::Statement *stmt;
	sql::ResultSet  *res;

	WCHAR sqlQuery[100];
	char sqlQueryEncoded[100];

	ObjectsContainer* gatherQuriedObjects(DatabaseObject *type); //собирает результаты запроса в контейнер в виде объектов
};

