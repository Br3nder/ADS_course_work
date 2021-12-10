#include <string>
#include <iostream>
#include "queue.h"
#include "stack.h"
using namespace std;
class Calc
{
  private:
    string expression_;
    string postfix_expression_;
    Queue<char>*  queue_expression;
    bool CheckForIncorrectInput();
    char GetTypeOfElement(char element);
 public:
  Calc(): expression_(""), postfix_expression_(""), queue_expression(new Queue<char>) {};
  Calc(string new_expression): expression_(new_expression) {};
  void setNewExpression(string new_expression) {expression_ = new_expression;}; 
  int getResult();
  int MakePostfixForm();
  string expression() {return expression_;};
  string postfix_expression() { return postfix_expression_; };
  ~Calc();
};

//this fun return the type of the char element
char Calc::GetTypeOfElement(char element)
{
    if (element == '(') return 'l'; // left bracket
    else if (element == ')') return 'r'; // right bracket
    else if (element == '+' || element == '-' || element == '/' || element == '*') return 'o'; //operator
    else if (element > 47 && element < 58) return 'n'; //number
    else return 'i'; //incorrect 
}

bool Calc::CheckForIncorrectInput() // 1 - All is correct, 0 - incorrect input
{
    char element = 0, prev_element = 0;
    int brackets_balance_counter = 0, operators_counter = 0, numbers_counter = 0;
    string message = "";
    int i;
    for (i = 0; i < expression_.length(); i++)
    {
        element = expression_[i];
        if (GetTypeOfElement(element) == 'o') operators_counter++;
        else if (GetTypeOfElement(element) == 'n') numbers_counter++;
        else if (element == '(') brackets_balance_counter++;
        else if (element == ')') brackets_balance_counter--;
        if (element == ')' && prev_element == 0) 
        { 
            message = "Expression start with close bracket!"; 
            break;
        }
        if (GetTypeOfElement(element) == 'o' && numbers_counter == 0)
        {
            message = "The Expression start with operator!";
            break;
        }
        if (brackets_balance_counter < 0)
        {
            message = "Extra close bracket in expression";
            break;
        }
        if (prev_element == '(' && GetTypeOfElement(element) == 'o')
        {
            message = "An operator after the open bracket or a number was missed!";
            break;
        }
        if (element == ')' && GetTypeOfElement(prev_element) == 'o')
        {
            i--;
            message = "An operator before the close bracket or a number was missed!";
            break;
        }
        if (numbers_counter - operators_counter < 0)
        {
            message = "Extra operator in expression!";
            break;
        }
        if (GetTypeOfElement(element) == 'i' && element != ' ')
        {
            message = "Invalide symbol was entered!";
            break;
        }
        prev_element = element;
    }
    if (brackets_balance_counter > 0 && i == expression_.length())
    {
        message = "Open brackets is more than closer!";
    }
    if (GetTypeOfElement(element) == 'o')
    {
        message = "Expression ends on operator!";
        i--;
    }
    if (message != "")
    {
        string mask = "\n";
        for (int j = 0; j < i; j++)
         {
             mask += " ";
         }
         mask += "^";
         cout << expression_ << mask << endl << message;
        return false;
    }
    return true;
}


int Calc::getResult()
{
    char element;
    string numer_in_string = "";
    int result, a, b;
    Stack<int>* stack = new Stack<int>;
    while (!queue_expression->IsEmpty())
    {
        while (GetTypeOfElement(queue_expression->first_element()->value()) == 'n')
        {
            numer_in_string += queue_expression->Dequeue()->value();
        }
        if(numer_in_string != "")stack->Push(new Item<int>(stoi(numer_in_string)));
        numer_in_string = "";
        if (GetTypeOfElement(queue_expression->first_element()->value()) == 'o')
        {
            a = stack->Pop()->value();
            b = stack->Pop()->value();
            if (queue_expression->first_element()->value() == '+') result = b + a;
            else if (queue_expression->first_element()->value() == '-') result = b - a;
            else if (queue_expression->first_element()->value() == '*') result = b * a;
            else if (queue_expression->first_element()->value() == '/' && a == 0)
            {
                cout << "Oh ... u done division by zero D:\n";
                return 0;
            }
            else if (queue_expression->first_element()->value() == '/') result = b / a;
            stack->Push(new Item<int>(result));
        }
        queue_expression->Dequeue();
    }
    if (!stack->IsEmpty())
    {
        return stack->Pop()->value();
    }
    else return 0;
}

int Calc::MakePostfixForm()
{
  if (!CheckForIncorrectInput())
  {
     return 0;
  }
  Stack<char>* stack = new Stack<char>();
  char element;
  for(int i = 0; i < expression_.length(); i++)
  {
    element = expression_[i];    
    Item<char>* new_element = new Item<char>(element);
    if (element > 47 && element < 58)
    {
      if (!queue_expression->IsEmpty())
          if (queue_expression->last_element()->value() > 47 && queue_expression->first_element()->value() < 58)
          {
              postfix_expression_ += ',';
              queue_expression->Enqueue(new Item<char>(','));
          }
      postfix_expression_ += element;
      queue_expression->Enqueue(new_element);
      while (expression_[i+1] > 47 && expression_[i+1] < 58)
      {
          element = expression_[++i];
          postfix_expression_ += element;
          queue_expression->Enqueue(new Item<char>(element));
      }
    }
    else if (element == '+' || element == '-' || element == '/' || element == '*') // if enter element is operator
    {
      if(stack->IsEmpty()) 
      {
        stack->Push(new_element);
      }
      else if (stack->top_element()->value() == '(') //if upper element in stack is '('
      {
          stack->Push(new_element);
      }
      else if ((element == '*' || element == '/') && (stack->top_element()->value() == '+' || stack->top_element()->value() == '-')) //if operator in stack is lower priority
      {
        stack->Push(new_element);
      }
      //if operator in stack is higher or equal priority
      else if ((element == '*' || element == '/') && (stack->top_element()->value() == '*' || stack->top_element()->value() == '/') || (element == '+' || element == '-') && (stack->top_element()->value() == '*' || stack->top_element()->value() == '/') || (element == '+' || element == '-') && (stack->top_element()->value() == '+' || stack->top_element()->value() == '-'))
      {
        while(!((element == '*' || element == '/') && (stack->top_element()->value() == '+' || stack->top_element()->value() == '-')) || stack->top_element()->value() == '(')
        {
            if (stack->IsEmpty()) break;
            postfix_expression_ += stack->top_element()->value();
            queue_expression->Enqueue(stack->Pop());
        }
        stack->Push(new_element);
      } 
    }
    else if (element == '(') //if enter element is '('
    {
        stack->Push(new_element);
    }
    else if (element == ')') //if enter element is ')'
    {
        while (stack->top_element()->value() != '(' && !stack->IsEmpty())
        {
            postfix_expression_ += stack->top_element()->value();
            queue_expression->Enqueue(stack->Pop());
        }
        Item<char>* tmp = stack->Pop();
        delete tmp;
    }
  }
  while(!stack->IsEmpty()) //unloading stack into the queue
  {
      postfix_expression_ += stack->top_element()->value();
      queue_expression->Enqueue(stack->Pop());
  }
}