#pragma once

#include "DatabaseObject.h"

class Sale : public DatabaseObject
{
public:
	Sale();
	Sale(char);
	~Sale();

	int id;
	int product_id;
	WCHAR product_name[100];
	int amount;
	int cost;

	LPWSTR related_name();

	void fillFromData(sql::ResultSet *data);
	virtual DatabaseObject* createSameObject();
	virtual int sizeOfSelf();

	virtual LPWSTR getUpdateSQL();
	virtual LPWSTR getDeleteSQL();
	virtual LPWSTR getSelectObjectSQL();
private:
	
};