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
	stmt->execute("USE `projects-database`");
}

std::vector<DatabaseObject>* DatabaseWrapper::getObjects(DatabaseObject *object)
{
	WCHAR tableName[50];
	mbstowcs(tableName, object->table, 50);

	WideCharToMultiByte(CP_UTF8, NULL, object->getSelectObjectSQL(), 100, sqlQueryEncoded, 100, NULL, NULL);

	stmt = con->createStatement();
	res = stmt->executeQuery(sqlQueryEncoded);
	
	std::vector<DatabaseObject>* list = new std::vector<DatabaseObject>();
	while (res->next())
	{
		DatabaseObject *newObject = object->createSameObject();
		newObject->fillFromData(res);
		list->push_back(*newObject);
	}

	return list;
}

void DatabaseWrapper::recreateDatabase()
{
	stmt->execute("CREATE TABLE IF NOT EXISTS `lecturer` (`name` varchar(100) NOT NULL, `id` int(10) NOT NULL AUTO_INCREMENT, PRIMARY KEY (`id`), UNIQUE KEY `name` (`name`)) DEFAULT CHARSET=utf8");
	stmt->execute("CREATE TABLE IF NOT EXISTS `student` (`name` varchar(100) NOT NULL, `id` int(10) NOT NULL AUTO_INCREMENT, `group` varchar(50) NOT NULL, PRIMARY KEY (`id`), UNIQUE KEY `name` (`name`)) DEFAULT CHARSET=utf8");
	stmt->execute("CREATE TABLE IF NOT EXISTS `project` (`task` varchar(100) NOT NULL, `dueTo` date DEFAULT NULL, `id` int(11) NOT NULL, `subject` varchar(50) NOT NULL, `completeness` int(10) unsigned NOT NULL DEFAULT '0', `student_id` int(10) DEFAULT NULL, `lecturer_id` int(10) DEFAULT NULL, PRIMARY KEY (`id`), KEY `student_ref` (`student_id`), KEY `lecturer_ref` (`lecturer_id`), CONSTRAINT `lecturer_ref` FOREIGN KEY (`lecturer_id`) REFERENCES `lecturer` (`id`), CONSTRAINT `student_ref` FOREIGN KEY (`student_id`) REFERENCES `student` (`id`)) DEFAULT CHARSET=utf8");
}