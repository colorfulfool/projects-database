struct RequestHeader //��������� �������
{
	char method[6]; //����� - GET, POST, PUT ��� DELETE
	char URI[50]; //������������� �������, ������������� usecase'� ��������� �����
	int bodySize; //������ ���� �������
};