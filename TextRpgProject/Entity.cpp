#include "Entity.h"

void Entity::setName(string _name)
{
	this->name = _name;
}

string Entity::getName() const
{
	return this->name;
}
