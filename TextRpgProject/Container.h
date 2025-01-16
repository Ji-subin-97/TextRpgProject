#pragma once

#include "Object.h"
#include "Box.h"
#include <vector>
#include <initializer_list>
#include <memory>

using namespace std;

class Container : public Box
{
    vector<shared_ptr<Object>> children;
private:
    void AddBorder() override;
public:
    Container();
    Container(Pos pos);
    ~Container();
    void AddObject(shared_ptr<Object> object);
    void AddObject(initializer_list<shared_ptr<Object>> objects);

    template <typename T>
    shared_ptr<T> FindObject(int id) const;
    vector<shared_ptr<Object>> GetChildren() const;
    void SetPos(Pos pos) override;
    void SetPos(int x, int y) override;
};

template <typename T>
shared_ptr<T> Container::FindObject(int id) const
{
    for (auto& object : children)
    {
        if (id == object->GetId()) {
            shared_ptr<T> newObject = dynamic_pointer_cast<T>(object);
            return newObject;
        }
    }

    return nullptr;
}


