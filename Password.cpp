#include "Password.h"
#include "Blowfish.h"

string generateRandomSalt(size_t length)
{
    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    random_device rd;
    mt19937 generator(rd());

    uniform_int_distribution<> distribution(0, characters.size() - 1);

    // Generate the salt
    string salt;
    for (size_t i = 0; i < length; ++i)
    {
        salt += characters[distribution(generator)];
    }

    return salt;
}

string generateSalt(size_t length)
{
    // Characters that can be used in the salt
    const string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

    // Random device and generator
    random_device rd;
    mt19937 generator(rd());

    // Distribution for generating random indices
    uniform_int_distribution<> distribution(0, characters.size() - 1);

    // Get the current time since epoch in milliseconds
    auto now = chrono::system_clock::now();
    auto epoch = now.time_since_epoch();
    auto milliseconds = chrono::duration_cast<chrono::milliseconds>(epoch).count();

    // Convert the time to a string
    stringstream timeStream;
    timeStream << milliseconds;

    // Generate the random part of the salt
    string randomPart;
    for (size_t i = 0; i < length - timeStream.str().size(); ++i)
    {
        randomPart += characters[distribution(generator)];
    }

    // Combine the time-based part and the random part
    string salt = timeStream.str() + randomPart;

    // If the salt is still shorter than the required length, append more random characters
    while (salt.size() < length)
    {
        salt += characters[distribution(generator)];
    }

    // Trim the salt to the desired length if necessary
    if (salt.size() > length)
    {
        salt = salt.substr(0, length);
    }

    return salt;
}

string generateHash(const string &password, const string &salt)
{
    string combine = password + salt;
    string combineHex = stringToHex(combine);
    Blowfish bf(combineHex);
    return bf.encrypt(stringToHex(password));
}

void storePassword(unordered_map<string, pair<string, string>> &passwordStorage, const string &username, const string &password)
{
    string salt = generateSalt(16);
    cout << "Salt: " << salt << endl;
    string hashPass = generateHash(password, salt);

    cout << "Encrypted: " << hashPass << endl;
    passwordStorage[username] = make_pair(hashPass, salt);
    cout << "Password for " << username << " stored successfully." << endl;
}
bool verifyPassword(const string &password)
{
    // Check length constraints
    if (password.length() < 8)
    {
        cout << "Password must be larger than 8 characters." << endl;
        return false;
    }
    return true;
}

bool verifyPasswordChange(const unordered_map<string, pair<string, string>> &passwordStorage, const string &username, const string &oldPassword, const string &newPassword)
{
    auto it = passwordStorage.find(username);
    if (it == passwordStorage.end())
    {
        cout << "User not found." << endl;
        return false;
    }

    string storedHash = it->second.first;
    string salt = it->second.second;
    string oldHashPass = generateHash(oldPassword, salt);

    if (storedHash != oldHashPass)
    {
        cout << "Old password does not match." << endl;
        return false;
    }

    if (oldPassword == newPassword)
    {
        cout << "New password cannot be the same as the old password." << endl;
        return false;
    }

    // if (newPassword.length() < 8 || newPassword.find_first_of("0123456789") == string::npos || newPassword.find_first_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ") == string::npos || newPassword.find_first_of("abcdefghijklmnopqrstuvwxyz") == string::npos)
    // {
    //     cout << "New password does not meet security standards." << endl;
    //     return false;
    // }

    return true;
}

void clearInputBuffer()
{
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}