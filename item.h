#pragma once
#include <cstddef>
using namespace std;

template <typename T>
class Item
{
private:
    T element_;
    Item* next_item_;
public:
    Item() : element_(NULL), next_item_(nullptr) {};
    Item(T new_element) : element_(new_element), next_item_(nullptr) {};
    T value() { if (element_) return element_; return 0; };
    void SetElement(T new_element) { element_ = new_element; };
    Item* next_item() { return next_item_; };
    void SetNextItem(Item* new_next_item) { next_item_ = new_next_item; };
};