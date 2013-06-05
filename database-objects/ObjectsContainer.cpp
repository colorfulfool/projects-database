#include "ObjectsContainer.h"

ObjectsContainer::ObjectsContainer(void)
{
	objectSize = 0;
	objectsCount = 0;
	storage = NULL;

	currentIndex = -1;
}

ObjectsContainer::ObjectsContainer(DatabaseObject *objectExample, int sizeTotal)
{
	storage = NULL;

	currentIndex = -1;

	objectSize = objectExample->sizeOfSelf();
	objectsCount = sizeTotal/objectSize;
}

ObjectsContainer::~ObjectsContainer(void)
{
}

void ObjectsContainer::append(DatabaseObject *object)
{
	if (storage == NULL) //если контейнер еще не инициализирован (и, соответственно, пуст)
	{
		objectSize = object->sizeOfSelf();
		storage = (char*)malloc(objectSize);
	}

	objectsCount++;
	storage = (char*)realloc(storage, objectSize*objectsCount);

	memcpy(storage + objectSize*(objectsCount-1), (void*)object, objectSize);
}

int ObjectsContainer::totalSize()
{
	return objectSize*objectsCount;
}

char* ObjectsContainer::dataPointer()
{
	return storage;
}

void ObjectsContainer::setDataPointer(char* pointer)
{
	storage = pointer;
}

bool ObjectsContainer::next()
{
	currentIndex++;

	if (currentIndex < objectsCount)
		return TRUE;
	else
		return FALSE;
}

DatabaseObject* ObjectsContainer::current()
{
	return (DatabaseObject*)(storage + objectSize*currentIndex);
}