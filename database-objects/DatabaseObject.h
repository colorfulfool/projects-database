#pragma once

#include <Windows.h>
#include <C:\Program Files\MySQL\MySQL Connector C++ 1.1.1\include\cppconn\resultset.h>

class DatabaseObject //представл€ет запись из базы данных в виде объекта
{
public:
	DatabaseObject();
	~DatabaseObject();

	virtual void fillFromData(sql::ResultSet *data); //заполн€ет пол€ объекта на основе данных из базы
	virtual LPWSTR getUpdateSQL(); //возвращает SQL-запрос, добавл€ющий объект в базу
	virtual LPWSTR getDeleteSQL();
	virtual LPWSTR getSelectObjectSQL();

	virtual DatabaseObject* createSameObject(); //фабричный метод, возвращает объект того же типа

	int id; //первичный ключ объекта в его таблице
	char table[50]; //название таблицы
private:
	
};