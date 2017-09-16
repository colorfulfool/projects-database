#include "ViewsCollection.h"
#include "DatabaseWrapper.h"
#include "ObjectsContainer.h"
#include "Product.h"
#include "Asset.h"
#include "Sale.h"
#include "Purchase.h"
#include "ValueObject.h"

#include <cppconn\exception.h>

ViewsCollection::ViewsCollection(void)
{
}

ViewsCollection::~ViewsCollection(void)
{
}

ObjectsContainer* ViewsCollection::allSales(char* method, char* requestBody)
{
	if (strcmp(method, "GET") == 0) //GET - значит выборка
		return DatabaseWrapper::instance()->getObjects(new Sale());

	if ((strcmp(method, "PUT") == 0)||(strcmp(method, "POST") == 0)) //PUT или POST - значит обновление
	{
		Sale *object = new Sale(*(Sale*)requestBody);

		ObjectsContainer *result; //разбираюсь с внешними ключами:
		result = DatabaseWrapper::instance()->getObjectsByAttribute(new Product(), L"name", object->product_name);
		if (result->next() == FALSE)
			return throwAnException("Foreign key error: no such lecturer"); //не вернулось ни одного объекта - что-то пошло не так, бросаю исключение
		Product* related_object = (Product*)(result->current());
		object->product_id = related_object->id;

		DatabaseWrapper::instance()->updateObject(object);
		return NULL;
	}

	if (strcmp(method, "DELETE") == 0) //DELETE - значит удаление
	{
		DatabaseWrapper::instance()->deleteObject(new Sale(*(Sale*)requestBody));
		return NULL;
	}
}

ObjectsContainer* ViewsCollection::productSales(char *method, char *requestBody)
{
	return DatabaseWrapper::instance()->getObjectsByAttribute(new Sale(), L"product_name", (LPCWSTR)requestBody);
}

ObjectsContainer* ViewsCollection::productPurchases(char method[6], char* requestBody)
{
	return DatabaseWrapper::instance()->getRelatedObjects(new Purchase(), (LPCWSTR)requestBody);
}

ObjectsContainer* ViewsCollection::allPurchases(char* method, char* requestBody)
{
	if (strcmp(method, "GET") == 0) //GET - значит выборка
		return DatabaseWrapper::instance()->getObjects(new Purchase());

	if ((strcmp(method, "PUT") == 0)||(strcmp(method, "POST") == 0)) //PUT или POST - значит обновление
	{
		Purchase *object = new Purchase(*(Purchase*)requestBody);

		ObjectsContainer *result; //разбираюсь с внешними ключами:
		result = DatabaseWrapper::instance()->getObjectsByAttribute(new Asset(), L"name", object->asset_name); //со ссылкой на преподавателя
		if (result->next() == FALSE)
			return throwAnException("Foreign key error: no such lecturer"); //не вернулось ни одного объекта - что-то пошло не так, бросаю исключение
		Asset* related_object = (Asset*)(result->current());
		object->asset_id = related_object->id;

		DatabaseWrapper::instance()->updateObject(object);
		return NULL;
	}

	if (strcmp(method, "DELETE") == 0) //DELETE - значит удаление
	{
		DatabaseWrapper::instance()->deleteObject(new Purchase(*(Purchase*)requestBody));
		return NULL;
	}
}

ObjectsContainer* ViewsCollection::calculateProfitability(ObjectsContainer* sales, ObjectsContainer* purchases, LPCWSTR valueName)
{
	int totalSpent=0, totalEarned=0;

	Sale *sale;
	while (sales->next())
	{
		sale = (Sale*)sales->current();

		totalEarned += sale->cost * sale->amount;
	}

	Purchase *purchase;
	while (purchases->next())
	{
		purchase = (Purchase*)purchases->current();

		totalSpent += purchase->cost * sale->amount;
	}

	float value = (totalEarned - totalSpent) / (float)totalSpent * 100;

	ValueObject *packedValue = new ValueObject();
	wcscpy(packedValue->name, valueName);
	swprintf(packedValue->value, L"%f%", value);

	ObjectsContainer *list = new ObjectsContainer();
	list->append(packedValue);

	return list;
}

ObjectsContainer* ViewsCollection::allProfitability(char method[6], char* requestBody)
{
	return ViewsCollection::calculateProfitability(
		allSales(method, requestBody),
		allPurchases(method, requestBody),
		L"Общая рентабельность"
	);
}

ObjectsContainer* ViewsCollection::productProfitability(char method[6], char* requestBody)
{
	return ViewsCollection::calculateProfitability(
		productSales(method, requestBody),
		productPurchases(method, requestBody),
		L"Рентабельность наименования продукции"
	);
}

ObjectsContainer* ViewsCollection::throwAnException(char* message)
{
	//std::string *messagePacked = new std::string(message);
	//throw sql::SQLException(*messagePacked);

	char msgString[300] = "FAIL";
	strcpy(msgString+5, message);

	return (ObjectsContainer*)msgString;
}