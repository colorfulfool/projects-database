#pragma once

#include "DatabaseObject.h"

class ObjectsContainer //контейнер/итератор, хранит потомков DatabaseObject, не зная их конкретного класса
{
public:
	ObjectsContainer(void);
	ObjectsContainer(DatabaseObject *example, int count); //позволяет сообщить контейнеру о классе хранимых объектов
	~ObjectsContainer(void);

	void append(DatabaseObject *object);
	int totalSize(); //общий размер хранилища (то есть всех объектов)

	char* dataPointer(); //возвращает указатель на хранилище
	
	void setDataPointer(char* pointer);
	bool next();
	DatabaseObject* current();

private:
	char* storage;
	int objectSize;
	int objectsCount;

	int currentIndex;
};

