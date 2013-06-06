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
	con = sql::mysql::get_driver_instance()->connect("tcp://127.0.0.1:3306", "root", "password");

	stmt = con->createStatement();
	stmt->execute("CREATE DATABASE IF NOT EXISTS `finance-database`"); //если базы данных еще нет, она будет создана
	stmt->execute("USE `finance-database`");
}

ObjectsContainer* DatabaseWrapper::getObjects(DatabaseObject *object)
{
	WideCharToMultiByte(CP_UTF8, NULL, object->getSelectObjectSQL(), 350, sqlQueryEncoded, 350, NULL, NULL);

	return gatherQuriedObjects(object);
}

ObjectsContainer* DatabaseWrapper::getRelatedObjects(DatabaseObject *object)
{
	// WideCharToMultiByte(CP_UTF8, NULL, object->getSelectRelatedSQL(), 350, sqlQueryEncoded, 350, NULL, NULL);

	return gatherQuriedObjects(object);
}

ObjectsContainer* DatabaseWrapper::getObjectsByAttribute(DatabaseObject *object, LPCWSTR attribute, LPCWSTR value)
{
	WCHAR queryCombined[350];
	swprintf(queryCombined, L"SELECT * FROM (%s) AS result WHERE `%s`='%s'", object->getSelectObjectSQL(), attribute, value);

	WideCharToMultiByte(CP_UTF8, NULL, queryCombined, 350, sqlQueryEncoded, 350, NULL, NULL);

	return gatherQuriedObjects(object);
}

ObjectsContainer* DatabaseWrapper::gatherQuriedObjects(DatabaseObject *type)
{
	stmt = con->createStatement();
	res = stmt->executeQuery(sqlQueryEncoded);

	ObjectsContainer* list = new ObjectsContainer();
	while (res->next())
	{
		DatabaseObject *newObject = type->createSameObject();
		newObject->fillFromData(res);
		list->append(newObject);
	}

	return list;
}

void DatabaseWrapper::recreateDatabase()
{
	stmt->execute("CREATE TABLE IF NOT EXISTS `lecturer` (`name` varchar(100) NOT NULL, `id` int(10) NOT NULL AUTO_INCREMENT, PRIMARY KEY (`id`), UNIQUE KEY `name` (`name`)) DEFAULT CHARSET=utf8");

	printf("Database structure has been recreated.");
}

void DatabaseWrapper::updateObject(DatabaseObject *object)
{
	WideCharToMultiByte(CP_UTF8, NULL, object->getUpdateSQL(), 350, sqlQueryEncoded, 350, NULL, NULL);

	stmt = con->createStatement();
	stmt->execute(sqlQueryEncoded);

	return;
}

void DatabaseWrapper::deleteObject(DatabaseObject *object)
{
	WideCharToMultiByte(CP_UTF8, NULL, object->getDeleteSQL(), 350, sqlQueryEncoded, 350, NULL, NULL);

	stmt = con->createStatement();
	stmt->execute(sqlQueryEncoded);

	return;
}