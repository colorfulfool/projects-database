#include "DatabaseWrapper.h"

DatabaseWrapper::DatabaseWrapper(void)
{
}

DatabaseWrapper::~DatabaseWrapper(void)
{
	delete con;
}

DatabaseWrapper* DatabaseWrapper::_instance = 0;

DatabaseWrapper* DatabaseWrapper::instance()
{
	if (_instance == 0)
	{
		_instance = new DatabaseWrapper();
	}
	return _instance;
}

void DatabaseWrapper::connectToDatabase()
{
	con = sql::mysql::get_driver_instance()->connect("tcp://127.0.0.1", "root", "password");
}

std::vector<DatabaseObject>* DatabaseWrapper::getObjects(DatabaseObject *object)
{
	WCHAR tableName[50];
	mbstowcs(tableName, object->table, 50);
	
	swprintf(sqlQuery, L"SELECT * FROM '%s'", tableName);

	stmt = con->createStatement();
	res = stmt->executeQuery(sql::SQLString());
	
	std::vector<DatabaseObject>* list = new std::vector<DatabaseObject>();
	while (res->next())
	{
		DatabaseObject *newObject = object->createSameObject();
		newObject->fillFromData(res);
		list->push_back(*newObject);
	}

	return list;
}