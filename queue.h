#pragma once
#include "item.h"
using namespace std;

template <class T>
class Queue
{
private:
    Item<T>* first_element_;
    Item<T>* last_element_;
public:
    Queue() : first_element_(nullptr), last_element_(nullptr) {};
    void Enqueue(Item<T>* new_element);
    Item<T>* Dequeue();
    bool IsEmpty() { if (!first_element_) return true; return false; };
    Item<T>* first_element() { if (first_element_) return first_element_; return nullptr; };
    Item<T>* last_element() { if (last_element_) return last_element_; return nullptr; };
};

template<typename T>
void Queue<T>::Enqueue(Item<T>* new_element)
{
    if (!first_element_)
    {
        first_element_ = new_element;
        first_element_->SetNextItem(nullptr);
        last_element_ = first_element_;
    }
    else
    {
        new_element->SetNextItem(last_element_);
        last_element_ = new_element;
    }
}

template<typename T>
Item<T>* Queue<T>::Dequeue()
{
    if (first_element_ && (first_element_ != last_element_))
    {
        Item<T>* cur_element = last_element_, * tmp;
        while (cur_element->next_item()->next_item() != nullptr)
        {
            cur_element = cur_element->next_item();
        }
        tmp = cur_element->next_item();
        first_element_ = cur_element;
        first_element_->SetNextItem(nullptr);
        return tmp;
    }
    else if (first_element_ && (first_element_ == last_element_))
    {
        Item<T>* tmp = first_element_;
        first_element_ = nullptr;
        last_element_ = nullptr;
        return tmp;
    }
    else
    {
        return nullptr;
    }
}