#include "RequestGenerator.h"
#include "DatabaseObject.h"
#include "Project.h"
#include "ObjectsContainer.h"
#include "Lecturer.h"
#include "Student.h"

RequestGenerator::RequestGenerator(void)
{
	socket_id = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_id == INVALID_SOCKET)
	{
		int error = WSAGetLastError();
		mainForm->MessageBox(L"Ќе удалось создать сокет.");
	}
}

int RequestGenerator::connectToServer(char *address, int port)
{
	memset(&server_address, 0, sizeof(struct sockaddr_in));
	server_address.sin_family = AF_INET; //IPv4
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = inet_addr(address);

	int returned = connect(socket_id, (const sockaddr*)&server_address, sizeof(struct sockaddr_in));
	if (returned != 0)
	{
		mainForm->MessageBox(L"Ќе удалось подключитьс€.");
	}

	return returned;
}

RequestGenerator::~RequestGenerator(void)
{
}

RequestGenerator* RequestGenerator::_instance = 0;

RequestGenerator* RequestGenerator::instance()
{
	if (_instance == 0)
	{
		_instance = new RequestGenerator();
	}
	return _instance;
}

ResponseBody RequestGenerator::sendRequest(char method[4], char URI[50], char* body, int bodySize)
{
	RequestHeader *header = new RequestHeader; //заголовок запроса

	strcpy(header->method, method);
	strcpy(header->URI, URI);
	header->bodySize = bodySize;

	send(socket_id, (char*)header, sizeof(RequestHeader), NULL);
	send(socket_id, body, bodySize, NULL);

	//тем временем сервер обраротал запрос

	ResponseHeader *response = new ResponseHeader;
	recv(socket_id, (char*)response, sizeof(RequestHeader), NULL); //принимаю заголовок ответа

	char *responseBody = (char*)malloc(response->bodySize);
	if (response->bodySize > 0)
		recv(socket_id, (char*)responseBody, response->bodySize, NULL);

	ResponseBody resp;
	if (strcmp(response->status, "OK") == 0)
	{
		resp.body = responseBody;
		resp.size = response->bodySize;

		return resp;
	} else if (strcmp(response->status, "FAIL") == 0) //если произошла ошибка
	{
		WCHAR *messageEncoded = (WCHAR*)calloc(response->bodySize, sizeof(WCHAR));
		mbstowcs(messageEncoded, responseBody, response->bodySize);
		mainForm->showError(messageEncoded); //показываю сообщение об этом
		
		resp.size = 0;
		return resp; //нуждаетс€ а проверке
	} else {
		mainForm->showError(L"Ќепон€тный ответ сервера.");
		
		resp.size = 0;
		return resp;
	}
}

void RequestGenerator::productSales(LPCWSTR productName)
{
	ResponseBody result = sendRequest("GET", "/sale/product", (char*)productName, (wcslen(productName)+1)*sizeof(WCHAR));

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayObjects(objects);
	}
}

void RequestGenerator::productPurchases(LPCWSTR productName)
{
	ResponseBody result = sendRequest("GET", "/purchase/product", (char*)productName, (wcslen(productName)+1)*sizeof(WCHAR));

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayObjects(objects);
	}
}

void RequestGenerator::allSales()
{
	ResponseBody result = sendRequest("GET", "/sale", NULL, 0);

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayObjects(objects);
	}
}

void RequestGenerator::allPurchases()
{
	ResponseBody result = sendRequest("GET", "/purchase", NULL, 0);

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayObjects(objects);
	}
}

void RequestGenerator::addSale(LPCWSTR product_name, int amount, int cost)
{
	Sale *newOne = new Sale();

	wcscpy(newOne->product_name, product_name);
	newOne->amount = amount;
	newOne->cost = cost;

	sendRequest("POST", "/sale", (char*)newOne, sizeof(Sale));
}

void RequestGenerator::addPurchase(LPCWSTR asset_name, int amount, int cost)
{
	Sale *newOne = new Sale();

	wcscpy(newOne->asset_name, asset_name);
	newOne->amount = amount;
	newOne->cost = cost;

	sendRequest("POST", "/purchase", (char*)newOne, sizeof(Sale));
}

void RequestGenerator::editSale(LPCWSTR product_name, int amount, int cost)
{
	Sale *newOne = new Sale();

	wcscpy(newOne->product_name, product_name);
	newOne->amount = amount;
	newOne->cost = cost;

	sendRequest("PUT", "/sale", (char*)newOne, sizeof(Sale));
}

void RequestGenerator::editPurchase(LPCWSTR asset_name, int amount, int cost)
{
	Sale *newOne = new Sale();

	wcscpy(newOne->asset_name, asset_name);
	newOne->amount = amount;
	newOne->cost = cost;

	sendRequest("PUT", "/purchase", (char*)newOne, sizeof(Sale));
}

void RequestGenerator::allProfitability()
{
	ResponseBody result = sendRequest("GET", "/profitability", NULL, 0);

		if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new ValueObject(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayValue(objects);
	}
}

void RequestGenerator::productProfitability(LPCWSTR productName)
{
	ResponseBody result = sendRequest("GET", "/profitability/product", (char*)productName, (wcslen(productName)+1)*sizeof(WCHAR));

		if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new ValueObject(), result.size);
		objects->setDataPointer(result.body);

		mainForm->displayValue(objects);
	}
}

void RequestGenerator::removeSale(int id)
{
	Sale *newOne = new Sale();

	newOne->id = id;

	sendRequest("DELETE", "/sale", (char*)newOne, sizeof(Sale));
}

void RequestGenerator::removePurchase(int id)
{
	Purchase *newOne = new Purchase();

	newOne->id = id;

	sendRequest("DELETE", "/purchase", (char*)newOne, sizeof(Purchase));
}

void RequestGenerator::setMainForm(CclientDlg *dialog)
{
	mainForm = dialog;
}

void RequestGenerator::fullReport()
{
	ResponseBody result = sendRequest("GET", "/sale", NULL, 0);

	if (result.size != 0)
	{
		ObjectsContainer *objects = new ObjectsContainer(new Project(), result.size);
		objects->setDataPointer(result.body);

		mainForm->saveTextReport(objects);
	}
}