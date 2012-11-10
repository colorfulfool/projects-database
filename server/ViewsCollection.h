#pragma once

class ViewsCollection
{
public:
	~ViewsCollection(void);

	static ViewsCollection* instance();
protected:
	ViewsCollection(void);
private:
	static ViewsCollection* _instance;
};

