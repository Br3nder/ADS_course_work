#include "item.h"

template<class T>
class Stack
{
private:
    Item<T>* top_element_ = nullptr;
public:
    Stack() : top_element_(nullptr) {};
    ~Stack();
    Item<T>* top_element() { return top_element_; };
    void Push(Item<T>* new_element);
    Item<T>* Pop();
    bool IsEmpty() { if (!top_element_) return true; return false; };
};

template<typename T>
void Stack<T>::Push(Item<T>* new_element)
{
  new_element->SetNextItem(top_element_);
  top_element_ = new_element;
}

template<typename T>
Item<T>* Stack<T>::Pop()
{
  Item<T>* tmp = nullptr;
  if(top_element_)
  {
    tmp = top_element_;
    top_element_ = top_element_->next_item();
  }
  return tmp;
}