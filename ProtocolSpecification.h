struct RequestHeader //заголовок запроса
{
	char method[7]; //метод - GET, POST, PUT или DELETE
	char URI[50]; //идентификатор ресурса, соответствует usecase'у серверной части
	int bodySize; //размер тела запроса
};

struct ResponseHeader //заголовок ответа
{
	char URI[50];
	char status[4]; //результат - OK или FAIL
	int bodySize;
};