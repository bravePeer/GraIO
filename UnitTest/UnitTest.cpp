#include "pch.h"
#include "CppUnitTest.h"
#include "../user.h"
#include "../utilities.h"
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;
using namespace sf;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(TestClassUser)
		{
			Assert::AreEqual( User::IsLogged(), false);
			User::Login(L"login", L"haslo");
			Assert::AreEqual(User::IsLogged(), true);
		}
		TEST_METHOD(TestFunctionAbsVector2i)
		{
			Vector2i a = absVector2i(Vector2i(-2, -3));
			Assert::AreEqual(a.x, 2);
			Assert::AreEqual(a.y, 3);
		}
	};
}
