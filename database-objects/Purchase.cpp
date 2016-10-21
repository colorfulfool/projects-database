#include "Purchase.h"

Purchase::Purchase()
{
	strcpy(table, "purchase");

	asset_id = 0;
}

Purchase::Purchase(char bullshit)
{

}

Purchase::~Purchase()
{
	
}

LPWSTR Purchase::related_name()
{
	return this->asset_name;
}

LPWSTR Purchase::getUpdateSQL()
{
	WCHAR query[350];

	if (this->id == 0) //если объект еще не добавлен в базу, то INSERT
	{
		swprintf(query, L"INSERT INTO `purchase` (`asset_id`, `amount`, `cost`) VALUES ('%d', '%d', '%d')", asset_id, amount, cost);
	} else { //иначе - UPDATE
		swprintf(query, L"UPDATE `purchase` SET `asset_id`='%d', `amount`='%d', `cost`='%d' WHERE `id` = %d", asset_id, amount, cost, this->id);
	}

	return query;
}

LPWSTR Purchase::getRelatedByNameSQL(LPCWSTR name)
{
	WCHAR query[350];

	swprintf(query, L"SELECT purchase.cost AS cost, product_asset.amount AS amount, product_asset.asset_id AS asset_id, '0' AS id FROM product INNER JOIN product_asset ON product_asset.product_id = product.id INNER JOIN purchase ON product_asset.asset_id = purchase.asset_id WHERE product.name = '%s'", name);

	return query;
}

LPWSTR Purchase::getDeleteSQL()
{
	WCHAR query[350];

	swprintf(query, L"DELETE FROM `purchase` WHERE `id` = %d", this->id);

	return query;
}

LPWSTR Purchase::getSelectObjectSQL()
{
	return L"SELECT purchase.id, amount, cost, asset_id, asset.name AS asset_name FROM `purchase` INNER JOIN `asset` ON purchase.asset_id=asset.id";
}

void Purchase::fillFromData(sql::ResultSet *data)
{
	this->id = data->getInt("id");
	asset_id = data->getInt("asset_id");
	amount = data->getInt("amount");
	cost = data->getInt("cost");
	MultiByteToWideChar(CP_UTF8, NULL, data->getString("asset_name")->c_str(), 50, this->asset_name, 50);
}

DatabaseObject* Purchase::createSameObject()
{
	return new Purchase();
}

int Purchase::sizeOfSelf()
{
	return sizeof(Purchase);
}