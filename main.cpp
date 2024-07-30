#include "Blowfish.h"

int main()
{
    string password = "123456789123"; //pass
    string salt = generateSalt(16);
    cout << "Salt: " << salt << endl;
    string hash = generateHash(password, salt);

    cout << "Encrypted: " << hash << endl;

    return 0;
}