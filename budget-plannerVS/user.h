#pragma once

#include <iostream>
#include <string>
#include <pqxx/pqxx>

class User
{
public:
	bool loginUser(std::string& inputUsername, std::string& inputPassword, pqxx::connection& activeConnection);
	bool registerUser(std::string& newUsername, std::string& newPassword, pqxx::connection& activeConnection);
	std::string getUsername();
private:
	std::string username;
};

