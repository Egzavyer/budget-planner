
#include "user.h"
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::hash;

bool User::loginUser(string inputUsername, string inputPassword, pqxx::connection& activeConnection) {
    hash<string> string_hash; //TODO: IMPLEMENT BETTER HASHING
    string hashedPassword = std::to_string(string_hash(inputPassword));

    pqxx::work tx(activeConnection);
    pqxx::result r = tx.exec("SELECT * FROM users WHERE username = '" + inputUsername + "' AND password = '" + hashedPassword + "'");
    tx.commit();

    if (r.empty()) {
		cout << "Invalid username or password." << endl;
		return false;
	} else if (r.size() > 1) {
        cout << "ERROR: Multiple users with the same username and password." << endl;
        return false;
    }

    cout << "User " << inputUsername << " logged in!" << endl;
    User::username = inputUsername;

    cout << "User: " + inputUsername << endl;
    cout << "Password: " + inputPassword << endl;
    exit(0);
}

bool User::registerUser(string newUsername, string newPassword,pqxx::connection& activeConnection) {
    hash<string> string_hash; //TODO: IMPLEMENT BETTER HASHING
    string hashedPassword = std::to_string(string_hash(newPassword));

    pqxx::work tx(activeConnection);
    tx.exec("INSERT INTO users (username, password) VALUES ('" + newUsername + "', '" + hashedPassword + "')");
    tx.commit();

    cout << "User registered!" << endl;
    cout << "User: " + newUsername << endl;
    cout << "Password: " + newPassword << endl;
    exit(0);
}
