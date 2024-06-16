#include "pch.h"
#include "CppUnitTest.h"
#include "user.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace budgetplannertest
{
	TEST_CLASS(budgetplannertest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			User user;
			user.logoutUser();
			std::string expected = "";
			Assert::AreEqual(expected, user.getUsername());
		}
	};
}
