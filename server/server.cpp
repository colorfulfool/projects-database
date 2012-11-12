#include "RequestProcessor.h"
#include "DatabaseWrapper.h"
#include "Project.h"

int main(int argc, char* argv[])
{
	DatabaseWrapper::instance()->connectToDatabase(); //���������� � ����� ������
	if ((argc > 1)&&(strcpy(argv[1], "--create-database")))
	{
		DatabaseWrapper::instance()->recreateDatabase(); //���������� ���� ������, ���� ������������ ����������
	}

	RequestProcessor *processor = RequestProcessor::instance(); 

	while (1) //������� ������������ �������
	{
		processor->mainLoopIteration();
	}

	return 0;
}

