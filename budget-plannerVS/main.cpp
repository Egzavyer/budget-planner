#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <fstream>
#include "user.h"


static std::string readConfig(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("ERROR: Unable to open configuration file. \n");
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.find("DB_CONNECTION_STRING=") == 0) {
            return line.substr(21);
        }
    }

    throw std::runtime_error("ERROR: DB_CONNECTION_STRING not found in configuration file. \n");
}

static pqxx::connection connectToDB() {
	std::string connection_string = readConfig("config.txt");
	pqxx::connection connection(connection_string);
	if (connection.is_open()) {
		std::cout << "Opened Database Successfully: " << connection.dbname() << std::endl;
	} else {
		throw std::runtime_error("ERROR: Unable to open database. \n");
	}
	return connection;
}

static void showMainMenu() {
    std::cout << "1. Login\n";
    std::cout << "2. Register\n";
    std::cout << "3. Exit\n";
    std::cout << "Choose: ";
}

static void handleMainMenuChoice(int choice, pqxx::connection& activeConnection) {
	User user;
	std::string inputUsername;
	std::string inputPassword;

	switch (choice) {
		case 1:
			std::cout << "Login...\n";
			std::cout << "Enter username: \n";
			std::cin >> inputUsername;
			std::cout << "Enter password: \n";
			std::cin >> inputPassword;

			if (user.loginUser(inputUsername, inputPassword, activeConnection)) {
				std::cout << "Login Successful! \n";
				std::cout << "Welcome, " << user.getUsername() << "\n\n";
			} else {
				throw std::runtime_error("ERROR: Login Failed. \n");
			}
			break;

		case 2:
			std::cout << "Register...\n";
			std::cout << "Enter username: \n";
			std::cin >> inputUsername;
			std::cout << "Enter password: \n";
			std::cin >> inputPassword;

			if (user.registerUser(inputUsername, inputPassword, activeConnection)) {
				std::cout << "Registration Successful! \n";
				std::cout << "Welcome, " << user.getUsername() << "\n\n";
			} else {
				throw std::runtime_error("ERROR: Registration Failed. \n");
			}
			break;

		case 3:
			std::cout << "Exiting...\n";
			break;

		default:
			throw std::invalid_argument("ERROR: Invalid choice. \n");
	}
}

int main() {
	int choice;

    std::cout << "Welcome to the CLI Budget Planner!" << std::endl;
    try{
        pqxx::connection c = connectToDB();

		//do {
		showMainMenu();
		std::cin >> choice;
		handleMainMenuChoice(choice, c);
		//} while (choice != 3);

    } catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}
}