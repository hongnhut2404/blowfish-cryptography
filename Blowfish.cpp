#include "Blowfish.h"

string stringToHex(const string &str)
{
    ostringstream oss;
    for (unsigned char c : str)
    {
        oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(c);
    }
    return oss.str();
}

void Blowfish::initialize()
{
    P = P_init;
    S = S_init;
}

string Blowfish::hexToBin(const string &plainText)
{
    string binary;
    // cout << plainText << endl;
    for (char c : plainText)
    {
        if (!isxdigit(c))
        {
            throw invalid_argument("Non-hexadecimal character encountered: " + string(1, c));
        }

        // Convert the hex character to its integer representation
        uint8_t num = stoi(string(1, c), nullptr, 16);
        // Convert the number to a binary string with 4 bits
        binary += bitset<4>(num).to_string();
    }

    return binary;
}

// Convert binary string to hex string
string Blowfish::binToHex(const string &plainText)
{
    stringstream ss;
    ss << hex << setw(plainText.length() / 4) << setfill('0') << stoul(plainText, nullptr, 2);
    return ss.str();
}

// XOR two hexadecimal strings of the same length
string Blowfish::xorHex(const string &a, const string &b)
{
    string binA = hexToBin(a);
    string binB = hexToBin(b);
    string binResult;
    for (size_t i = 0; i < binA.size(); ++i)
    {
        binResult += (binA[i] ^ binB[i]) ? '1' : '0';
    }
    return binToHex(binResult);
}

// Addition modulo 2^32
string Blowfish::addBin(const string &a, const string &b)
{
    uint32_t n1 = stoul(a, nullptr, 16);
    uint32_t n2 = stoul(b, nullptr, 16);
    uint32_t result = (n1 + n2) % 0x100000000;
    stringstream ss;
    ss << hex << setw(8) << setfill('0') << result;
    return ss.str();
}

// Function F
string Blowfish::f(const string &plainText)
{
    string a[4];
    for (int i = 0; i < 8; i += 2)
    {
        uint8_t col = stoul(hexToBin(plainText.substr(i, 2)), nullptr, 2);
        stringstream ss;
        ss << hex << S[i / 2][col];
        a[i / 2] = ss.str();
    }
    string ans = addBin(a[0], a[1]);
    ans = xorHex(ans, a[2]);
    ans = addBin(ans, a[3]);
    return ans;
}

// Generate subkeys
void Blowfish::keyGenerate(const std::string &key)
{
    size_t key_length = key.length();
    size_t P_size = P.size();

    if (key_length < 4)
    {
        std::cerr << "Error: Key length must be at least 32 bits (4 bytes)." << std::endl;
        return;
    }
    if (key_length > 56)
    {
        std::cerr << "Error: Key length exceeds maximum of 448 bits (56 bytes)." << std::endl;
        return;
    }

    size_t j = 0;
    for (size_t i = 0; i < P_size; ++i)
    {
        // Extract 8 characters (4 bytes) from the key
        std::string subkey = key.substr(j, 8);
        if (subkey.length() < 8)
        {
            // Pad with zeros if the substring is less than 8 bytes
            subkey.append(8 - subkey.length(), '0');
        }

        // XOR with P[i]
        P[i] = xorHex(P[i], subkey);

        // Print subkey information
        std::cout << "subkey " << (i + 1) << ": "
                  << std::hex << std::setw(8) << std::setfill('0') << P[i]
                  << std::dec << std::endl;

        j = (j + 8) % key_length;
    }
}

// Round function
string Blowfish::round(int time, const string &plainText)
{
    string left = plainText.substr(0, 8);
    string right = plainText.substr(8, 8);
    left = xorHex(left, P[time]);
    string fOut = f(left);
    right = xorHex(fOut, right);
    cout << "round " << time << ": " << right << left << endl;
    return right + left;
}

string Blowfish::encrypt(const string &plainText)
{
    string pt = plainText;
    keyGenerate(key);
    for (int i = 0; i < 16; ++i)
    {
        pt = round(i, pt);
    }
    string right = pt.substr(0, 8);
    string left = pt.substr(8, 8);
    right = xorHex(right, P[16]);
    left = xorHex(left, P[17]);
    return left + right;
}
