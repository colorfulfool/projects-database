#pragma once
class DatabaseWrapper
{
public:
	~DatabaseWrapper(void);

	static DatabaseWrapper* instance();
protected:
	DatabaseWrapper(void);
private:
	static DatabaseWrapper* _instance;
};

