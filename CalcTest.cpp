#include "pch.h"
#include "CppUnitTest.h"
#include "../course_work/calc_inf_to_pref.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalcTest
{
	TEST_CLASS(CalcTest)
	{
	public:
		Calc* calc = new Calc();
		TEST_METHOD(postfix_form)
		{
			calc->setNewExpression("5*6+(2-9)");
			calc->MakePostfixForm();
			Assert::IsTrue("5,6*2,9-+" == calc->postfix_expression());
		}
		TEST_METHOD(result_by_postfix_form)
		{
			calc->setNewExpression("5*6+(2-9)");
			calc->MakePostfixForm();
			Assert::IsTrue(23 == calc->getResult());
		}
		TEST_METHOD(zero)
		{
			calc->setNewExpression("5*6+(2-9/0)");
			calc->MakePostfixForm();
			Assert::IsTrue(0 == calc->getResult());
		}
		TEST_METHOD(brackets_invalid_start)
		{
			calc->setNewExpression(")5*6+(2-9)");
			calc->MakePostfixForm();
			Assert::IsTrue(0 == calc->getResult());
		}
		TEST_METHOD(brackets_close_count)
		{
			calc->setNewExpression("5*6+(2-9))");
			calc->MakePostfixForm();
			Assert::IsTrue(0 == calc->getResult());
		}
		TEST_METHOD(invalide_symbol)
		{
			calc->setNewExpression("5*6!+(2-9)");
			calc->MakePostfixForm();
			Assert::IsTrue(0 == calc->getResult());
		}
		TEST_METHOD(operator_start)
		{
			calc->setNewExpression("+5*6+(2-9)");
			calc->MakePostfixForm();
			Assert::IsTrue(0 == calc->getResult());
		}
		TEST_METHOD(operator_double)
		{
			calc->setNewExpression("5-*6+(2-9)");
			calc->MakePostfixForm();
			Assert::IsTrue(0 == calc->getResult());
		}
		TEST_METHOD(operator_in_brackets)
		{
			Calc* calc2 = new Calc();
			calc->setNewExpression("5*6+(+2-9)");
			calc2->setNewExpression("5*6+(2-9+)");
			calc->MakePostfixForm();
			calc2->MakePostfixForm();
			Assert::IsTrue(calc->getResult() + calc2->getResult() == 0);
		}
	};
}
