#include "ValueObject.h"

ValueObject::ValueObject()
{

}

ValueObject::ValueObject(char bullshit)
{

}

ValueObject::~ValueObject()
{
	
}


DatabaseObject* ValueObject::createSameObject()
{
	return new ValueObject();
}

int ValueObject::sizeOfSelf()
{
	return sizeof(ValueObject);
}

// LPWSTR ValueObject::getUpdateSQL()
// {
// 	WCHAR query[350];

// 	if (this->id == 0) //если объект еще не добавлен в базу, то INSERT
// 	{
// 		swprintf(query, L"INSERT INTO `purchase` (`asset_id`, `amount`, `cost`) VALUES ('%s', '%d', '%d')", asset_id, amount, cost);
// 	} else { //иначе - UPDATE
// 		swprintf(query, L"UPDATE `purchase` SET `asset_id`='%d', `amount`='%d', `cost`='%d' WHERE `id` = %d", asset_id, amount, cost, this->id);
// 	}

// 	return query;
// }

// LPWSTR ValueObject::getDeleteSQL()
// {
// 	WCHAR query[350];

// 	swprintf(query, L"DELETE FROM `purchase` WHERE `id` = %d", this->id);

// 	return query;
// }

// LPWSTR ValueObject::getSelectObjectSQL()
// {
// 	return L"SELECT purchase.id, amount, cost, asset.name AS asset_name FROM `purchase` INNER JOIN `asset` ON purchase.asset_id=asset.id";
// }

// void ValueObject::fillFromData(sql::ResultSet *data)
// {
// 	this->id = data->getInt("id");
// 	asset_id = data->getInt("asset_id");
// 	amount = data->getInt("amount");
// 	cost = data->getInt("cost");
// 	MultiByteToWideChar(CP_UTF8, NULL, data->getString("asset_name")->c_str(), 50, this->asset_name, 50);
// }