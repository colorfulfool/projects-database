

class DatabaseObject
{
public:
	DatabaseObject();
	~DatabaseObject();

	virtual char* getUpdateSQL();
	virtual char* getDeleteSQL();
private:
	int id; //��������� ���� ������� � ��� �������
}