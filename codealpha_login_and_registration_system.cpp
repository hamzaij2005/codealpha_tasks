#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Function to check if a username already exists
bool usernameExists(const string& username) {
    ifstream file("users.txt");
    string line, storedUsername;

    while (getline(file, line)) {
        size_t sep = line.find(',');
        if (sep != string::npos) {
            storedUsername = line.substr(0, sep);
            if (storedUsername == username) {
                return true;
            }
        }
    }
    return false;
}

// Function to register a new user
void registerUser() {
    string username, password;
    cout << "Enter new username: ";
    cin >> username;

    if (usernameExists(username)) {
        cout << "Username already exists. Try a different one.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << "," << password << endl;
    file.close();

    cout << "Registration successful!\n";
}

// Function to log in an existing user
void loginUser() {
    string username, password, line;
    bool loginSuccess = false;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    while (getline(file, line)) {
        size_t sep = line.find(',');
        string storedUsername = line.substr(0, sep);
        string storedPassword = line.substr(sep + 1);

        if (storedUsername == username && storedPassword == password) {
            loginSuccess = true;
            break;
        }
    }

    if (loginSuccess)
        cout << "Login successful!\n";
    else
        cout << " Login failed. Invalid username or password.\n";
}

// Main menu
int main() {
    int choice;
    do {
        cout << "\n---- Login & Registration System ----\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Choose an option (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid option. Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
