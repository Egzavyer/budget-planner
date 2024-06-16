#include "user.h"

std::string User::getUsername() {
	return username;
}

bool User::loginUser(std::string& inputUsername, std::string& inputPassword, pqxx::connection& activeConnection)
{
	std::hash<std::string> string_hash; //TODO: IMPLEMENT BETTER HASHING
	std::string hashedPassword = std::to_string(string_hash(inputPassword));

	try {
		pqxx::work txn(activeConnection);
		pqxx::result result = txn.exec("SELECT * FROM users WHERE username = '" + inputUsername + "' AND password = '" + hashedPassword + "'");
		txn.commit();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	username = inputUsername;
	return true;
}

bool User::registerUser(std::string& newUsername, std::string& newPassword, pqxx::connection& activeConnection)
{
	std::hash<std::string> string_hash;
	std::string hashedPassword = std::to_string(string_hash(newPassword));

	try {
		pqxx::work txn(activeConnection);
		txn.exec("INSERT INTO users (username, password) VALUES ('" + newUsername + "', '" + hashedPassword + "')");
		txn.commit();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
		return false;
	}
	username = newUsername;
	return true;
}
