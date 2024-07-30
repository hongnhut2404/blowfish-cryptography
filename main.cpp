#include "Blowfish.h"

int main()
{
    string key = "aabb09182736ccdd";
    Blowfish blowfish(key);

    string plaintext = "123456abcd132536";
    string encrypted = blowfish.encrypt(plaintext);

    cout << "Encrypted: " << encrypted << endl;
    // string decrypted = blowfish.decrypt(encrypted);
    // cout << "Decrypted: " << decrypted << endl;

    return 0;
}