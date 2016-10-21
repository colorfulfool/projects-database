#pragma once

#include "DatabaseObject.h"

class Purchase : public DatabaseObject
{
public:
	Purchase();
	Purchase(char);
	~Purchase();

	int id;
	int asset_id;
	WCHAR asset_name[100];
	int amount;
	int cost;

	LPWSTR related_name();

	void fillFromData(sql::ResultSet *data);
	virtual DatabaseObject* createSameObject();
	virtual int sizeOfSelf();

	virtual LPWSTR getUpdateSQL();
	virtual LPWSTR getDeleteSQL();
	virtual LPWSTR getSelectObjectSQL();

	virtual LPWSTR getRelatedByNameSQL(LPCWSTR name);
private:
	
};