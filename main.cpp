#include "Blowfish.h"

int main()
{
    string password = "hellowor"; //pass
    string salt = generateRandomSalt(16 - password.length());
    cout << salt << endl;
    string hash = generateHash(password, salt);

    cout << "Encrypted: " << hash << endl;

    return 0;
}