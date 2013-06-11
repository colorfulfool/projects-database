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
	if (strcmp(method, "GET") == 0) //GET - ������ �������
		return DatabaseWrapper::instance()->getObjects(new Sale());

	if ((strcmp(method, "PUT") == 0)||(strcmp(method, "POST") == 0)) //PUT ��� POST - ������ ����������
	{
		Sale *object = new Sale(*(Sale*)requestBody);

		ObjectsContainer *result; //���������� � �������� �������:
		result = DatabaseWrapper::instance()->getObjectsByAttribute(new Product(), L"name", object->product_name);
		if (result->next() == FALSE)
			return throwAnException("Foreign key error: no such lecturer"); //�� ��������� �� ������ ������� - ���-�� ����� �� ���, ������ ����������
		Product* related_object = (Product*)(result->current());
		object->product_id = related_object->id;

		DatabaseWrapper::instance()->updateObject(object);
		return NULL;
	}

	if (strcmp(method, "DELETE") == 0) //DELETE - ������ ��������
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
	if (strcmp(method, "GET") == 0) //GET - ������ �������
		return DatabaseWrapper::instance()->getObjects(new Purchase());

	if ((strcmp(method, "PUT") == 0)||(strcmp(method, "POST") == 0)) //PUT ��� POST - ������ ����������
	{
		Purchase *object = new Purchase(*(Purchase*)requestBody);

		ObjectsContainer *result; //���������� � �������� �������:
		result = DatabaseWrapper::instance()->getObjectsByAttribute(new Asset(), L"name", object->asset_name); //�� ������� �� �������������
		if (result->next() == FALSE)
			return throwAnException("Foreign key error: no such lecturer"); //�� ��������� �� ������ ������� - ���-�� ����� �� ���, ������ ����������
		Asset* related_object = (Asset*)(result->current());
		object->asset_id = related_object->id;

		DatabaseWrapper::instance()->updateObject(object);
		return NULL;
	}

	if (strcmp(method, "DELETE") == 0) //DELETE - ������ ��������
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
		L"����� ��������������"
	);
}

ObjectsContainer* ViewsCollection::productProfitability(char method[6], char* requestBody)
{
	return ViewsCollection::calculateProfitability(
		productSales(method, requestBody),
		productPurchases(method, requestBody),
		L"�������������� ������������ ���������"
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