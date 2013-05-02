

#include "BodyUserData.h"
#include <stdlib.h>
#include <string.h>

BodyUserData::BodyUserData(char* name)
{
	_name = 0;
	_name = (char*)malloc(strlen(name)+1);
	strcpy(_name,name);
}

void BodyUserData::setName(char* name)
{
	if(0 != _name)
		free(_name);
	_name = (char*)malloc(strlen(name)+1);
	strcpy(_name,name);
}

char* BodyUserData::getName()
{
	return _name;
}

void BodyUserData::setId(int id)
{
	_id = id;
}

int BodyUserData::getId()
{
	return _id;
}

void BodyUserData::setValue(int value)
{
	_value = value;
}

int BodyUserData::getValue()
{
	return _value;
}