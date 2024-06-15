#include <iostream>
#include <string>
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

int main() {
    cout << "Welcome to the CLI Budget Planner!" << endl;
}