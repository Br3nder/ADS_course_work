#include <iostream>
#include "calc_inf_to_pref.h"

using namespace std;

int main()
{
	Calc* calc = new Calc();
	string expression = "5*6+(2-9)/";
	calc->setNewExpression(expression);
	calc->MakePostfixForm();
	string answer = calc->postfix_expression();
	cout << answer << endl; // answer must be 56*29-+ , but have empty line(?) need: check alghoritms again, firstly if's in calc. If it isn't work, test for stack and queue
	cout << "ANSWER IS: " << calc->getResult();
}