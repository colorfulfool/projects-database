#include "RequestProcessor.h"
#include "DatabaseWrapper.h"
#include "Project.h"

#include <process.h>

#define PORT 1234

void client_thread(void *socket_to_use)
{
	RequestProcessor *newProcessor = new RequestProcessor((int)socket_to_use); //новый Processor будет обрабатывать запросы
	newProcessor->mainLoopIteration();

	delete newProcessor; //клиент отключился - удаляю Processor, завершаю поток
	closesocket((int)socket_to_use);

	return;
}

int main(int argc, char* argv[])
{
	int listening_socket, working_socket;

	DatabaseWrapper::instance()->connectToDatabase(); //соединяюсь с базой данных
	if ((argc > 1)&&(strcpy(argv[1], "--create-database")))
	{
		DatabaseWrapper::instance()->recreateDatabase(); //пересоздаю базу данных, если пользователь потребовал
	}

	struct sockaddr_in server_address, client_address;
	int size_of_address = sizeof(struct sockaddr_in);

	listening_socket = socket(AF_INET, SOCK_STREAM, 0); //создаю сокет

	memset(&server_address, 0, sizeof(struct sockaddr_in));
	server_address.sin_family = AF_INET; //IPv4
	server_address.sin_port = htons(PORT);
	server_address.sin_addr.s_addr = inet_addr("0.0.0.0");

	bind(listening_socket, (struct sockaddr *)&server_address, sizeof(server_address));

	listen(listening_socket, SOMAXCONN);

	printf("Serving requests at %s:%d...\n", inet_ntoa(server_address.sin_addr), PORT);

	while (1) //начинаю обрабатывать запросы
	{
		working_socket = accept(listening_socket, (struct sockaddr *)&client_address, &size_of_address); //принимаю подключение клиента

		printf("Client %s connected.\n", inet_ntoa(client_address.sin_addr));
		_beginthread(client_thread, 0, (void*)working_socket);
	}

	return 0;
}

