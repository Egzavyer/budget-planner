#include "pch.h"
#include "CppUnitTest.h"
#include "user.h"
#include "user.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace budgetplannertest
{
	TEST_CLASS(budgetplannertest)
	{
	private:
		static pqxx::connection* connection;

	public:
		TEST_CLASS_INITIALIZE(Initialize)
		{
			connection = new pqxx::connection("host=localhost port=5432 dbname=budget-planner-test user=testuser password=1234");
			connection->prepare("insert_user", "INSERT INTO users (username, password) VALUES ($1, $2)");
			connection->prepare("get_user", "SELECT * FROM users WHERE username = $1 AND password = $2");
		}
		TEST_METHOD(TestConnection) {
			Assert::IsTrue(connection->is_open());
		}

		TEST_METHOD(TestRegisterUser) {
			User user;
			std::string username = "testuser";
			std::string password = "testpassword";
			Assert::IsTrue(user.registerUser(username, password, *connection));
		}

		TEST_METHOD(TestLoginUser) {
			User user;
			std::string username = "testuser";
			std::string password = "testpassword";
			Assert::IsTrue(user.loginUser(username, password, *connection));
		}
	};
	pqxx::connection* budgetplannertest::connection = nullptr;
}
