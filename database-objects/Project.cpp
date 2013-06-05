#include "Project.h"

Project::Project()
{
	strcpy(table, "project");

	student_id = 0; //изначально внешие ключи пусты, соответственно - 0
	lecturer_id = 0;
}

Project::Project(char bullshit)
{

}

Project::~Project()
{
	
}

LPWSTR Project::getUpdateSQL()
{
	WCHAR query[350];

	if (this->id == 0) //если объект еще добавлен в базу, то INSERT
	{
		swprintf(query, L"INSERT INTO `project` (`task`, `dueTo`, `subject`, `completeness`, `student_id`, `lecturer_id`) VALUES ('%s', '%s', '%s', %d, %d, %d)", task, dueTo, subject, completeness, student_id, lecturer_id);
	} else { //иначе - UPDATE
		swprintf(query, L"UPDATE `project` SET `task`='%s', `dueTo`='%s', `subject`='%s', `completeness`=%d, `student_id`=%d, `lecturer_id`=%d WHERE `id` = %d", task, dueTo, subject, completeness, student_id, lecturer_id, this->id);
	}

	return query;
}

LPWSTR Project::getDeleteSQL()
{
	WCHAR query[350];

	swprintf(query, L"DELETE FROM `project` WHERE `id` = %d", this->id);

	return query;
}

LPWSTR Project::getSelectObjectSQL()
{
	return L"SELECT project.id, task, subject, dueTo, completeness, student_id, lecturer_id, lecturer.name AS lecturer, student.name AS student, student.group AS student_group FROM `project` INNER JOIN `lecturer` ON project.lecturer_id=lecturer.id INNER JOIN `student` ON project.student_id=student.id"; //нужен join для внешних ключей
}

void Project::fillFromData(sql::ResultSet *data)
{
	this->id = data->getInt("id");
	MultiByteToWideChar(CP_UTF8, NULL, data->getString("task")->c_str(), 100, this->task, 100); //таблища уже с именами и айдишниками будет
	MultiByteToWideChar(CP_UTF8, NULL, data->getString("subject")->c_str(), 50, this->subject, 50);
	this->completeness = data->getInt("completeness");
	MultiByteToWideChar(CP_UTF8, NULL, data->getString("dueTo")->c_str(), 50, this->dueTo, 50);
	this->student_id = data->getInt("student_id");
	this->lecturer_id = data->getInt("lecturer_id");
	MultiByteToWideChar(CP_UTF8, NULL, data->getString("lecturer")->c_str(), 100, this->lecturer, 100);
	MultiByteToWideChar(CP_UTF8, NULL, data->getString("student")->c_str(), 100, this->student, 100);
}

DatabaseObject* Project::createSameObject()
{
	return new Project();
}

int Project::sizeOfSelf()
{
	return sizeof(Project);
}