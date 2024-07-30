#include "Blowfish.h"
#include "Password.h"

int main()
{
    unordered_map<string, pair<string, string>> passwordStorage;
    int choice;

    while (true)
    {
        cout << "1. Store Password" << endl;
        cout << "2. Change Password" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1)
        {
            string username, password;
            cout << "Enter username: ";
            cin >> username;
            clearInputBuffer();
            cout << "Enter password: ";
            getline(cin, password);
            if (verifyPassword(password))
            {
                storePassword(passwordStorage, username, password);
            }
            else{
                cout << "Create password failed" << endl;
            }
        }
        else if (choice == 2)
        {
            string username, oldPassword, newPassword;
            cout << "Enter username: ";
            cin >> username;
            clearInputBuffer();
            cout << "Enter old password: ";
            getline(cin, oldPassword);
            cout << "Enter new password: ";
            getline(cin, newPassword);

            if (verifyPasswordChange(passwordStorage, username, oldPassword, newPassword))
            {
                storePassword(passwordStorage, username, newPassword);
                cout << "Password changed successfully." << endl;
            }
            else
            {
                cout << "Password change failed." << endl;
            }
        }
        else if (choice == 3)
        {
            break;
        }
        else
        {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;

    return 0;
}