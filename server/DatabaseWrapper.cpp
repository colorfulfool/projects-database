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

ObjectsContainer* DatabaseWrapper::getObjects(DatabaseObject *object)
{
	WideCharToMultiByte(CP_UTF8, NULL, object->getSelectObjectSQL(), 350, sqlQueryEncoded, 350, NULL, NULL);

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
	stmt->execute("CREATE TABLE IF NOT EXISTS `student` (`name` varchar(100) NOT NULL, `id` int(10) NOT NULL AUTO_INCREMENT, `group` varchar(50) NOT NULL, PRIMARY KEY (`id`), UNIQUE KEY `name` (`name`)) DEFAULT CHARSET=utf8");
	stmt->execute("CREATE TABLE IF NOT EXISTS `project` (`task` varchar(100) NOT NULL, `dueTo` date DEFAULT NULL, `id` int(11) NOT NULL, `subject` varchar(50) NOT NULL, `completeness` int(10) unsigned NOT NULL DEFAULT '0', `student_id` int(10) DEFAULT NULL, `lecturer_id` int(10) DEFAULT NULL, PRIMARY KEY (`id`), KEY `student_ref` (`student_id`), KEY `lecturer_ref` (`lecturer_id`), CONSTRAINT `lecturer_ref` FOREIGN KEY (`lecturer_id`) REFERENCES `lecturer` (`id`), CONSTRAINT `student_ref` FOREIGN KEY (`student_id`) REFERENCES `student` (`id`)) DEFAULT CHARSET=utf8");

	printf("Database structure has been recreated.");
}