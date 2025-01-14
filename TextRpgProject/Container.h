#pragma once

#include "Object.h"
#include "Box.h"
#include <vector>
#include <initializer_list>

using namespace std;

class Container : public Box
{
    vector<Object*> children;
private:
    void AddBorder() override;
public:
    Container();
    Container(Pos pos);
    ~Container();
    void AddObject(Object* object);
    void AddObject(initializer_list<Object*> objects);
    Object* FindObject(int id) const;
    vector<Object*> GetChildren() const;
    void SetPos(Pos pos) override;
    void SetPos(int x, int y) override;
};

