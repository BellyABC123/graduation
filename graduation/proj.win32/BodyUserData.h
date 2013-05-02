


#ifndef __BODY_USER_DATA__
#define __BODY_USER_DATA__


class BodyUserData
{
private:
	char* _name;
	int _id;
	int _value;

public:
	BodyUserData(char* name);
	void setName(char* name);
	char* getName();

	void setValue(int value);
	int getValue();

	void setId(int id);
	int getId();
};


#endif 
