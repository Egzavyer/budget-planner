#ifndef BUDGET_PLANNER_USER_H
#define BUDGET_PLANNER_USER_H

#include <iostream>
#include <string>
#include <pqxx/pqxx>

using std::string;
using std::cout;
using std::cin;
using std::endl;

class User {
public:
    bool loginUser(string inputUsername, string inputPassword, pqxx::connection& activeConnection);
    bool registerUser(string newUsername, string newPassword, pqxx::connection& activeConnection);
    string getUsername() { return username; }
private:
    string username;
    string password;
};


#endif //BUDGET_PLANNER_USER_H
