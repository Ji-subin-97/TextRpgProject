#pragma once

#include "Object.h"
#include "Box.h"
#include <vector>

using namespace std;

class Container : public Box
{
    vector<Object*> children;
private:
    void AddBorder() override;
public:
    Container();
    Container(Pos pos);
    void AddObject(Object* object);
    vector<Object*> GetChildren() const;
    void SetPos(Pos pos) override;
    void SetPos(int x, int y) override;
};

