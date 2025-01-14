#pragma once
#include <string>

using namespace std;

class Entity
{
private:
    string name;

public:
    Entity() = default;
    virtual ~Entity() = default;
    void setName(string _name);
    string getName() const;
};