#include "Sale.h"

Sale::Sale()
{
	strcpy(table, "sale");

	product_id = 0;
}

Sale::Sale(char bullshit)
{

}

Sale::~Sale()
{
	
}

LPWSTR Sale::related_name()
{
	return this->product_name;
}

LPWSTR Sale::getUpdateSQL()
{
	WCHAR query[350];

	if (this->id == 0) //если объект еще не добавлен в базу, то INSERT
	{
		swprintf(query, L"INSERT INTO `sale` (`product_id`, `amount`, `cost`) VALUES ('%d', '%d', '%d')", product_id, amount, cost);
	} else { //иначе - UPDATE
		swprintf(query, L"UPDATE `sale` SET `product_id`='%d', `amount`='%d', `cost`='%d' WHERE `id` = %d", product_id, amount, cost, this->id);
	}

	return query;
}

LPWSTR Sale::getDeleteSQL()
{
	WCHAR query[350];

	swprintf(query, L"DELETE FROM `sale` WHERE `id` = %d", this->id);

	return query;
}

LPWSTR Sale::getSelectObjectSQL()
{
	return L"SELECT sale.id, amount, cost, product_id, product.name AS product_name FROM `sale` INNER JOIN `product` ON sale.product_id=product.id";
}

void Sale::fillFromData(sql::ResultSet *data)
{
	this->id = data->getInt("id");
	product_id = data->getInt("product_id");
	amount = data->getInt("amount");
	cost = data->getInt("cost");
	MultiByteToWideChar(CP_UTF8, NULL, data->getString("product_name")->c_str(), 50, this->product_name, 50);
}

DatabaseObject* Sale::createSameObject()
{
	return new Sale();
}

int Sale::sizeOfSelf()
{
	return sizeof(Sale);
}