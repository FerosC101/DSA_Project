#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <ctime>
#include <cstdlib>

using namespace std;


struct User {
    string username;
    string password;
    vector<string>cart;
};

class UserManager {
private:
    unordered_map<string, User> users;
    const string user_file = "users.txt";
    const string admin_username = "BryAiNiVi";
    const string admin_password = "BryAiNiVi";

    void load_users() {
        ifstream file(user_file);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                istringstream iss(line);
                User user;
                iss >> user.username >> user.password;
                users[user.username] = user;

            }
            file.close();
        }
    }

    void save_users() {
        ofstream file(user_file);
        if (file.is_open()) {
            for (const auto& pair : users) {
                file << pair.second.username << " "
                     << pair.second.password << "\n";
            }
            file.close();
        }

    }

public:
    UserManager() {
        load_users();
    }

    ~UserManager() {
        save_users();
    }

    bool register_user(const string& username, const string& password) {
        if (users.find(username) != users.end()) {
            return false;
        }
        users[username] = {username, password};
        save_users();
        return true;
    }

    bool login_user(const string& username, const string& password) {
        if (users.find(username) == users.end()) {
            return false;
        }
        return users[username].password == password;
    }
};

int main() {
    UserManager userManager;
    string username;
    string password;

    cout << "1. Register" << endl;
    cout << "2. Log in" << endl;
    cout << "3. Admin Login" << endl;
    cout << "4. Exit" << endl;
    cout << "Enter choice: ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Enter Username: ";
        cin >> username;
        cout << "Enter Password: ";
        cin >> password;
        if (userManager.register_user(username, password)) {
            cout << "Registration successful!" << endl;
        } else {
            cout << "Username already exists!" << endl;
        }
    }
}
