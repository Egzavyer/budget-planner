
#include "user.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::hash;

bool User::loginUser(string inputUsername, string inputPassword) {
    cout << "User: " + inputUsername << endl;
    cout << "Password: " + inputPassword << endl;
    exit(0);
}

bool User::registerUser(string newUsername, string newPassword,pqxx::connection& activeConnection) {
    hash<string> string_hash;
    string hashedPassword = std::to_string(string_hash(newPassword));

    pqxx::work tx(activeConnection);
    tx.exec("INSERT INTO users (username, password) VALUES ('" + newUsername + "', '" + hashedPassword + "')");
    tx.commit();

    cout << "User registered!" << endl;
    cout << "User: " + newUsername << endl;
    cout << "Password: " + newPassword << endl; //TODO: HASH PASSWORD
    exit(0);
}
