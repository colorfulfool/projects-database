

class DatabaseObject
{
public:
	DatabaseObject();
	~DatabaseObject();

	virtual char* getUpdateSQL();
	virtual char* getDeleteSQL();
private:
	int id; //первичный ключ объекта в его таблице
}