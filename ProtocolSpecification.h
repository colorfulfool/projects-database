struct RequestHeader //��������� �������
{
	char method[4]; //����� - GET, POST, PUT ��� DELETE
	char URI[50]; //������������� �������, ������������� usecase'� ��������� �����
	int bodySize; //������ ���� �������
}