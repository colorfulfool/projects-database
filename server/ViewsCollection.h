#pragma once
#include <vector>
#include "../database-objects/DatabaseObject.h"
#include "ObjectsContainer.h"

class ViewsCollection
{
public:
	~ViewsCollection(void);

	static ObjectsContainer* allSales(char method[6], char* requestBody); //нужен для операций над курсовыми (выборка, добавление, etc)
	static ObjectsContainer* productSales(char method[6], char* requestBody);
	static ObjectsContainer* productPurchases(char method[6], char* requestBody, LPCWSTR valueName);

	static ObjectsContainer* allPurchases(char method[6], char* requestBody); //для операций над студентами

	static ObjectsContainer* allProfitability(char method[6], char* requestBody);
	static ObjectsContainer* productProfitability(char method[6], char* requestBody);
	// static ObjectsContainer* assetProfitability(char method[6], char* requestBody);

	static ObjectsContainer* throwAnException(char* message);
protected:
	ViewsCollection(void);
private:
	static float calculateProfitability(ObjectsContainer* sales, ObjectsContainer* purchases);
	
};

