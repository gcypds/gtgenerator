#ifndef GTGLOBALWIDGETS_H
#define GTGLOBALWIDGETS_H

class GTGlobalWidgets {

public:	
	static GTGlobalWidgets * Instance();		

private:
	GTGlobalWidgets();

	static GTGlobalWidgets * _instance;
};

#endif // GTGLOBALWIDGETS_H
