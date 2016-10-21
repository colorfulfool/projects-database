#include "Asset.h"

Asset::Asset()
{
	strcpy(table, "sale");

}

Asset::Asset(char bullshit)
{

}

Asset::~Asset()
{
	
}

// LPWSTR Asset::getUpdateSQL()
// {
// 	WCHAR query[350];

// 	if (this->id == 0) //если объект еще не добавлен в базу, то INSERT
// 	{
// 		swprintf(query, L"INSERT INTO `sale` (`product_id`, `amount`, `cost`) VALUES ('%s', '%d', '%d')", product_id, amount, cost);
// 	} else { //иначе - UPDATE
// 		swprintf(query, L"UPDATE `sale` SET `product_id`='%d', `amount`='%d', `cost`='%d' WHERE `id` = %d", product_id, amount, cost, this->id);
// 	}

// 	return query;
// }

// LPWSTR Asset::getDeleteSQL()
// {
// 	WCHAR query[350];

// 	swprintf(query, L"DELETE FROM `sale` WHERE `id` = %d", this->id);

// 	return query;
// }

LPWSTR Asset::getSelectObjectSQL()
{
	return L"SELECT id, name FROM `asset`";
}

void Asset::fillFromData(sql::ResultSet *data)
{
	this->id = data->getInt("id");
	MultiByteToWideChar(CP_UTF8, NULL, data->getString("name")->c_str(), 50, this->name, 50);
}

DatabaseObject* Asset::createSameObject()
{
	return new Asset();
}

int Asset::sizeOfSelf()
{
	return sizeof(Asset);
}