#include "RequestProcessor.h"
#include "DatabaseWrapper.h"
#include "Project.h"

int main(int argc, char* argv[])
{
	DatabaseWrapper::instance()->connectToDatabase(); //соединяюсь с базой данных
	if ((argc > 1)&&(strcpy(argv[1], "--create-database")))
	{
		DatabaseWrapper::instance()->recreateDatabase(); //пересоздаю базу данных, если пользователь потребовал
	}

	RequestProcessor *processor = RequestProcessor::instance(); 

	while (1) //начинаю обрабатывать запросы
	{
		processor->mainLoopIteration();
	}

	return 0;
}

