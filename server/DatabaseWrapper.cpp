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
	stmt->execute("CREATE DATABASE IF NOT EXISTS `finance-database`"); //РµСЃР»Рё Р±Р°Р·С‹ РґР°РЅРЅС‹С… РµС‰Рµ РЅРµС‚, РѕРЅР° Р±СѓРґРµС‚ СЃРѕР·РґР°РЅР°
	stmt->execute("USE `finance-database`");
}

ObjectsContainer* DatabaseWrapper::getObjects(DatabaseObject *object)
{
	WideCharToMultiByte(CP_UTF8, NULL, object->getSelectObjectSQL(), 350, sqlQueryEncoded, 350, NULL, NULL);

	return gatherQuriedObjects(object);
}

ObjectsContainer* DatabaseWrapper::getRelatedObjects(DatabaseObject *object, LPCWSTR relatedName)
{
	//int needed = WideCharToMultiByte(CP_UTF8, NULL, object->getRelatedByNameSQL(relatedName), -1, sqlQueryEncoded, 0, NULL, NULL);
	// WideCharToMultiByte(CP_UTF8, NULL, object->getRelatedByNameSQL(relatedName) + 150, -1, sqlQueryEncoded + 150, 350, NULL, NULL);
	WideCharToMultiByte(CP_UTF8, NULL, object->getRelatedByNameSQL(relatedName), -1, sqlQueryEncoded, 350, NULL, NULL);

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
	stmt->execute("CREATE TABLE IF NOT EXISTS `product` (  `name` varchar(100) NOT NULL,  `id` int(11) NOT NULL AUTO_INCREMENT,  PRIMARY KEY (`id`)) DEFAULT CHARSET=utf8");
	stmt->execute("CREATE TABLE IF NOT EXISTS `sale` (  `id` int(11) NOT NULL AUTO_INCREMENT,  `product_id` int(10) NOT NULL,  `cost` int(10) unsigned NOT NULL DEFAULT '0',  `amount` int(10) unsigned NOT NULL DEFAULT '0',  PRIMARY KEY (`id`),  KEY `product_ref` (`product_id`),  CONSTRAINT `product_ref` FOREIGN KEY (`product_id`) REFERENCES `product` (`id`)) DEFAULT CHARSET=utf8");
	stmt->execute("CREATE TABLE IF NOT EXISTS `asset` (  `name` varchar(100) NOT NULL,  `id` int(11) NOT NULL AUTO_INCREMENT,  PRIMARY KEY (`id`)) DEFAULT CHARSET=utf8");
	stmt->execute("CREATE TABLE IF NOT EXISTS `purchase` (  `id` int(11) NOT NULL AUTO_INCREMENT,  `asset_id` int(10) NOT NULL,  `cost` int(10) unsigned NOT NULL DEFAULT '0',  `amount` int(10) unsigned NOT NULL DEFAULT '0',  PRIMARY KEY (`id`),  KEY `asset_ref` (`asset_id`),  CONSTRAINT `asset_ref` FOREIGN KEY (`asset_id`) REFERENCES `asset` (`id`)) DEFAULT CHARSET=utf8");
	stmt->execute("CREATE TABLE IF NOT EXISTS `product_asset` (  `id` int(11) NOT NULL AUTO_INCREMENT,  `asset_id` int(10) NOT NULL,  `product_id` int(10) NOT NULL,  `amount` int(10) unsigned NOT NULL DEFAULT '0',  PRIMARY KEY (`id`),  KEY `asset_ref` (`asset_id`),  KEY `product_ref` (`product_id`),  CONSTRAINT `m2m_asset_ref` FOREIGN KEY (`asset_id`) REFERENCES `asset` (`id`),  CONSTRAINT `m2m_product_ref` FOREIGN KEY (`product_id`) REFERENCES `product` (`id`)) DEFAULT CHARSET=utf8");
	
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