#pragma once
#include <stdlib.h>
#include <string>
//#include <windows.h>
#include "clientDlg.h"

#include "..\ProtocolSpecification.h"

class CclientDlg;

struct ResponseBody //содержит тело ответа и размер этого тела
{
	int size;
	char *body;
};

class RequestGenerator
{
public:
	~RequestGenerator(void);

	static RequestGenerator* instance();

	int connectToServer(char *address, int port);
	ResponseBody sendRequest(char method[4], char URI[50], char* body, int bodySize);

	void allSales();
	void productSales(LPCWSTR productName);
	void productPurchases(LPCWSTR productName);
	void allPurchases();

	void allProfitability();
	void productProfitability(LPCWSTR productName);

	void addSale(LPCWSTR product_name, int amount, int cost);
	void addPurchase(LPCWSTR asset_name, int amount, int cost);
	void editSale(LPCWSTR product_name, int amount, int cost);
	void editPurchase(LPCWSTR asset_name, int amount, int cost);

	void removePurchase(int id);
	void removeSale(int id);
	void fullReport();

	void setMainForm(CclientDlg *dialog);
protected:
	RequestGenerator(void);
private:
	static RequestGenerator* _instance;

	int socket_id;
	sockaddr_in server_address;

	CclientDlg *mainForm;
};

