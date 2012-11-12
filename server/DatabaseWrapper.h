#pragma once
#include "mysql_connection.h"
#include "mysql_driver.h"
#include <cppconn\driver.h>
#include <cppconn\statement.h>
#include <cppconn\resultset.h>
#include "sqlstring.h"
#include <vector>

#include "DatabaseObject.h"

class DatabaseWrapper
{
public:
	~DatabaseWrapper(void);

	static DatabaseWrapper* instance();

	void connectToDatabase();

	std::vector<DatabaseObject>* getObjects(DatabaseObject *object); //возвращает все объекты указанного типа
	std::vector<DatabaseObject>* getObjectsByAttribute(DatabaseObject *object, LPCWSTR attribute, LPCWSTR value); //возращает объекты указанного типа, имеющие указанное значение атрибута
	//RET addObject(DatabaseObject *object);
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
};

