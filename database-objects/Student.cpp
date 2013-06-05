#include "Student.h"

Student::Student()
{
	strcpy(table, "student");
}

Student::Student(char bullshit)
{

}

Student::~Student()
{
	
}

LPWSTR Student::getUpdateSQL()
{
	WCHAR query[350];

	if (this->id == 0) //если объект еще добавлен в базу, то INSERT
	{
		swprintf(query, L"INSERT INTO `student` (`name`, `group`) VALUES ('%s', '%s')", name, group);
	} else { //иначе - UPDATE
		swprintf(query, L"UPDATE `student` SET `name`='%s', `group`='%s' WHERE `id` = %d", name, group, this->id);
	}

	return query;
}

LPWSTR Student::getDeleteSQL()
{
	WCHAR query[350];

	swprintf(query, L"DELETE FROM `student` WHERE `id` = %d", this->id);

	return query;
}

LPWSTR Student::getSelectObjectSQL()
{
	return L"SELECT * FROM `student`";
}

void Student::fillFromData(sql::ResultSet *data)
{
	this->id = data->getInt("id");
	MultiByteToWideChar(CP_UTF8, NULL, data->getString("name")->c_str(), 100, this->name, 100);
	MultiByteToWideChar(CP_UTF8, NULL, data->getString("group")->c_str(), 50, this->group, 50);
}

DatabaseObject* Student::createSameObject()
{
	return new Student();
}

int Student::sizeOfSelf()
{
	return sizeof(Student);
}