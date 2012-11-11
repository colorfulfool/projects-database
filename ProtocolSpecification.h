struct RequestHeader //��������� �������
{
	char method[6]; //����� - GET, POST, PUT ��� DELETE
	char URI[50]; //������������� �������, ������������� usecase'� ��������� �����
	int bodySize; //������ ���� �������
};

struct ResponseHeader //��������� ������
{
	char URI[50];
	char status[4]; //��������� - OK ��� FAIL
	int bodySize;
};