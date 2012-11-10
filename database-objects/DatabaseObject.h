class DatabaseObject
{
public:
	DatabaseObject();
	~DatabaseObject();

	virtual char* getUpdateSQL();
private:
	int id; //первичный ключ объекта в его таблице
}