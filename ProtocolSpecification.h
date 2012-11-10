struct RequestHeader //заголовок запроса
{
	char method[4]; //метод - GET, POST, PUT или DELETE
	char URI[50]; //идентификатор ресурса, соответствует usecase'у серверной части
	int bodySize; //размер тела запроса
}