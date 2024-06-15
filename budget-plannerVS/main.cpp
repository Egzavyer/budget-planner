#include <iostream>
#include <string>
#include "user.h"
#include <pqxx/pqxx>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::exception;

string readConfig(const string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("ERROR: Unable to open configuration file. \n");
    }

    string line;
    while (std::getline(file, line)) {
        if (line.find("DB_CONNECTION_STRING=") == 0) {
            return line.substr(21);
        }
    }

    throw std::runtime_error("ERROR: DB_CONNECTION_STRING not found in configuration file. \n");
}


void showMainMenu() {
    cout << "Main Menu: " << endl;
    cout << "1: Login" << endl;
    cout << "2: Register" << endl;
    cout << "3: Exit" << endl;
    cout << "Choose: " << endl;
}

void showBudgetMenu() {
    cout << "Budget Menu: " << endl;
	cout << "1: Add Expense" << endl;
	cout << "2: Add Income" << endl;
	cout << "3: View Budget" << endl;
	cout << "4: Exit" << endl;
	cout << "Choose: " << endl;

}

bool handleLogin(User& user) {
    string connectionString = readConfig("config.txt");

    pqxx::connection c(connectionString);
    std::cout << "Connected to " << c.dbname() << '\n';

    string inputUsername;
    string inputPassword;

    cout << "Username: " << endl;
    cin >> inputUsername;
    cout << "Password: " << endl;
    cin >> inputPassword;

    if (user.loginUser(inputUsername, inputPassword, c) == true) {
		cout << "User: " + user.getUsername() << endl;
        return true;
	}
	else {
		return false;
	}
}

bool handleRegister(User& user) {
    string connectionString = readConfig("config.txt");

    pqxx::connection c(connectionString);
    std::cout << "Connected to " << c.dbname() << '\n';

    string inputUsername;
    string inputPassword;

    cout << "Username: " << endl;
    cin >> inputUsername;
    cout << "Password: " << endl;
    cin >> inputPassword;

    if (user.registerUser(inputUsername, inputPassword, c) == true) {
        cout << "User: " + user.getUsername() << endl;
        return true;
    }
    else {
        return false;
    }
}

bool handleMenuChoice(string& choice) {
    User user;
    try {
        if (choice == "1") {
            cout << "Login..." << endl;
            if (handleLogin(user)) {
                return true;
            }
            //Login
        }
        else if (choice == "2") {
            cout << "Register..." << endl;
            if (handleRegister(user)) {
				return true;
			}
            //Register
        }
        else if (choice == "3") {
            cout << "Exiting..." << endl;
            exit(0);
        }
        else {
            throw std::invalid_argument("ERROR: Invalid Input \n");
        }
    }
    catch (exception& e) {
        cout << e.what() << endl;
    }
}

bool handleBudgetChoice(string& choice) {
    if (choice == "1") {
        cout << "Add Expense..." << endl;
        //Add Expense
    }
    else if (choice == "2") {
        cout << "Add Income..." << endl;
        //Add Income
    }
    else if (choice == "3") {
        cout << "View Budget..." << endl;
        //View Budget
    }
    else if (choice == "4") {
        cout << "Exiting..." << endl;
        return true;
    }
    else {
        cout << "ERROR: Invalid Input \n";
    }
    return false;
}

int main() {
    cout << "Welcome to the CLI Budget Planner!" << endl;
    while (true) {
        string choice;
        showMainMenu();
        cin >> choice;
        if (handleMenuChoice(choice)) {
            showBudgetMenu();
            cin >> choice;
            if (handleBudgetChoice(choice)) {
                break;
            }
		}
    }
}