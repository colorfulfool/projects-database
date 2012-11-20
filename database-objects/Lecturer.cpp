#include "Lecturer.h"

Lecturer::Lecturer()
{
	strcpy(table, "lecturer");
}

Lecturer::Lecturer(char bullshit)
{

}

Lecturer::~Lecturer()
{
	
}

LPWSTR Lecturer::getUpdateSQL()
{
	WCHAR query[350];

	if (this->id == 0) //если объект еще добавлен в базу, то INSERT
	{
		swprintf(query, L"INSERT INTO `lecturer` (`name`) VALUES ('%s')", name);
	} else { //иначе - UPDATE
		swprintf(query, L"UPDATE `lecturer` SET `name`='%s' WHERE `id` = %d", name, this->id);
	}

	return query;
}

LPWSTR Lecturer::getDeleteSQL()
{
	WCHAR query[350];

	swprintf(query, L"DELETE FROM `lecturer` WHERE `id` = %d", this->id);

	return query;
}

LPWSTR Lecturer::getSelectObjectSQL()
{
	return L"SELECT * FROM `lecturer`";
}

void Lecturer::fillFromData(sql::ResultSet *data)
{
	this->id = data->getInt("id");
	MultiByteToWideChar(CP_UTF8, NULL, data->getString("name")->c_str(), 100, this->name, 100);
}

DatabaseObject* Lecturer::createSameObject()
{
	return new Lecturer();
}

int Lecturer::sizeOfSelf()
{
	return sizeof(Lecturer);
}