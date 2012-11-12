#pragma once

#include <Windows.h>

class DatabaseObject //представл€ет запись из базы данных в виде объекта
{
public:
	DatabaseObject();
	~DatabaseObject();

	virtual LPWSTR getUpdateSQL(); //возвращает SQL-запрос, добавл€ющий объект в базу
	virtual LPWSTR getDeleteSQL();

	int id; //первичный ключ объекта в его таблице
	char table[50]; //название таблицы
private:
	
};