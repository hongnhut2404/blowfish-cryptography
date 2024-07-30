#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>

using namespace std;

class Blowfish
{
private:
    vector<uint32_t> P;
    vector<vector<uint32_t>> S;

    const vector<uint32_t> P_init = {
        0x243F6A88, 0x85A308D3, 0x13198A2E, 0x03707344, 0xA4093822, 0x299F31D0, 0x082EFA98, 0xEC4E6C89,
        0x452821E6, 0x38D01377, 0xBE5466CF, 0x34E90C6C, 0xC0AC29B7, 0xC97C50DD, 0x3F84D5B5, 0xB5470917,
        0x9216D5D9, 0x8979FB1B};

    const vector<vector<uint32_t>> S_init = {
        {/* S0 */
         0xd1310ba6, 0x98dfb5ac, 0x2ffd72db, 0xd01adfb7, 0xb8e1afed,
         0x6a267e96, 0xba7c9045, 0xf12c7f99, 0x24a19947, 0xb3916cf7,
         0x0801f2e2, 0x858efc16, 0x636920d8, 0x71574e69, 0xa458fea3,
         0xf4933d7e, 0x0d95748f, 0x728eb658, 0x718bcd58, 0x82154aee,
         0x7b54a41d, 0xc25a59b5, 0x9c30d539, 0x2af26013, 0xc5d1b023,
         0x286085f0, 0xca417918, 0xb8db38ef, 0x8e79dcb0, 0x603a180e,
         0x6c9e0e8b, 0xb01e8a3e, 0xd71577c1, 0xbd314b27, 0x78af2fda,
         0x55605c60, 0xe65525f3, 0xaa55ab94, 0x57489862, 0x63e81440,
         0x55ca396a, 0x2aab10b6, 0xb4cc5c34, 0x1141e8ce, 0xa15486af,
         0x7c72e993, 0xb3ee1411, 0x636fbc2a, 0x2ba9c55d, 0x741831f6,
         0xce5c3e16, 0x9b87931e, 0xafd6ba33, 0x6c24cf5c, 0x7a325381,
         0x28958677, 0x3b8f4898, 0x6b4bb9af, 0xc4bfe81b, 0x66282193,
         0x61d809cc, 0xfb21a991, 0x487cac60, 0x5dec8032, 0xef845d5d,
         0xe98575b1, 0xdc262302, 0xeb651b88, 0x23893e81, 0xd396acc5,
         0x0f6d6ff3, 0x83f44239, 0x2e0b4482, 0xa4842004, 0x69c8f04a,
         0x9e1f9b5e, 0x21c66842, 0xf6e96c9a, 0x670c9c61, 0xabd388f0,
         0x6a51a0d2, 0xd8542f68, 0x960fa728, 0xab5133a3, 0x6eef0b6c,
         0x137a3be4, 0xba3bf050, 0x7efb2a98, 0xa1f1651d, 0x39af0176,
         0x66ca593e, 0x82430e88, 0x8cee8619, 0x456f9fb4, 0x7d84a5c3,
         0x3b8b5ebe, 0xe06f75d8, 0x85c12073, 0x401a449f, 0x56c16aa6,
         0x4ed3aa62, 0x363f7706, 0x1bfedf72, 0x429b023d, 0x37d0d724,
         0xd00a1248, 0xdb0fead3, 0x49f1c09b, 0x075372c9, 0x80991b7b,
         0x25d479d8, 0xf6e8def7, 0xe3fe501a, 0xb6794c3b, 0x976ce0bd,
         0x04c006ba, 0xc1a94fb6, 0x409f60c4, 0x5e5c9ec2, 0x196a2463,
         0x68fb6faf, 0x3e6c53b5, 0x1339b2eb, 0x3b52ec6f, 0x6dfc511f,
         0x9b30952c, 0xcc814544, 0xaf5ebd09, 0xbee3d004, 0xde334afd,
         0x660f2807, 0x192e4bb3, 0xc0cba857, 0x45c8740f, 0xd20b5f39,
         0xb9d3fbdb, 0x5579c0bd, 0x1a60320a, 0xd6a100c6, 0x402c7279,
         0x679f25fe, 0xfb1fa3cc, 0x8ea5e9f8, 0xdb3222f8, 0x3c7516df,
         0xfd616b15, 0x2f501ec8, 0xad0552ab, 0x323db5fa, 0xfd238760,
         0x53317b48, 0x3e00df82, 0x9e5c57bb, 0xca6f8ca0, 0x1a87562e,
         0xdf1769db, 0xd542a8f6, 0x287effc3, 0xac6732c6, 0x8c4f5573,
         0x695b27b0, 0xbbca58c8, 0xe1ffa35d, 0xb8f011a0, 0x10fa3d98,
         0xfd2183b8, 0x4afcb56c, 0x2dd1d35b, 0x9a53e479, 0xb6f84565,
         0xd28e49bc, 0x4bfb9790, 0xe1ddf2da, 0xa4cb7e33, 0x62fb1341,
         0xcee4c6e8, 0xef20cada, 0x36774c01, 0xd07e9efe, 0x2bf11fb4,
         0x95dbda4d, 0xae909198, 0xeaad8e71, 0x6b93d5a0, 0xd08ed1d0,
         0xafc725e0, 0x8e3c5b2f, 0x8e7594b7, 0x8ff6e2fb, 0xf2122b64,
         0x8888b812, 0x900df01c, 0x4fad5ea0, 0x688fc31c, 0xd1cff191,
         0xb3a8c1ad, 0x2f2f2218, 0xbe0e1777, 0xea752dfe, 0x8b021fa1,
         0xe5a0cc0f, 0xb56f74e8, 0x18acf3d6, 0xce89e299, 0xb4a84fe0,
         0xfd13e0b7, 0x7cc43b81, 0xd2ada8d9, 0x165fa266, 0x80957705,
         0x93cc7314, 0x211a1477, 0xe6ad2065, 0x77b5fa86, 0xc75442f5,
         0xfb9d35cf, 0xebcdaf0c, 0x7b3e89a0, 0xd6411bd3, 0xae1e7e49,
         0x00250e2d, 0x2071b35e, 0x226800bb, 0x57b8e0af, 0x2464369b,
         0xf009b91e, 0x5563911d, 0x59dfa6aa, 0x78c14389, 0xd95a537f,
         0x207d5ba2, 0x02e5b9c5, 0x83260376, 0x6295cfa9, 0x11c81968,
         0x4e734a41, 0xb3472dca, 0x7b14a94a, 0x1b510052, 0x9a532915,
         0xd60f573f, 0xbc9bc6e4, 0x2b60a476, 0x81e67400, 0x08ba6fb5,
         0x571be91f, 0xf296ec6b, 0x2a0dd915, 0xb6636521, 0xe7b9f9b6,
         0xff34052e, 0xc5855664, 0x53b02d5d, 0xa99f8fa1, 0x08ba4799,
         0x6e85076a},
        {/* S1 */
         0x4b7a70e9, 0xb5b32944, 0xdb75092e, 0xc4192623, 0xad6ea6b0,
         0x49a7df7d, 0x9cee60b8, 0x8fedb266, 0xecaa8c71, 0x699a17ff,
         0x5664526c, 0xc2b19ee1, 0x193602a5, 0x75094c29, 0xa0591340,
         0xe4183a3e, 0x3f54989a, 0x5b429d65, 0x6b8fe4d6, 0x99f73fd6,
         0xa1d29c07, 0xefe830f5, 0x4d2d38e6, 0xf0255dc1, 0x4cdd2086,
         0x8470eb26, 0x6382e9c6, 0x021ecc5e, 0x09686b3f, 0x3ebaefc9,
         0x3c971814, 0x6b6a70a1, 0x687f3584, 0x52a0e286, 0xb79c5305,
         0xaa500737, 0x3e07841c, 0x7fdeae5c, 0x8e7d44ec, 0x5716f2b8,
         0xb03ada37, 0xf0500c0d, 0xf01c1f04, 0x0200b3ff, 0xae0cf51a,
         0x3cb574b2, 0x25837a58, 0xdc0921bd, 0xd19113f9, 0x7ca92ff6,
         0x94324773, 0x22f54701, 0x3ae5e581, 0x37c2dadc, 0xc8b57634,
         0x9af3dda7, 0xa9446146, 0x0fd0030e, 0xecc8c73e, 0xa4751e41,
         0xe238cd99, 0x3bea0e2f, 0x3280bba1, 0x183eb331, 0x4e548b38,
         0x4f6db908, 0x6f420d03, 0xf60a04bf, 0x2cb81290, 0x24977c79,
         0x5679b072, 0xbcaf89af, 0xde9a771f, 0xd9930810, 0xb38bae12,
         0xdccf3f2e, 0x5512721f, 0x2e6b7124, 0x501adde6, 0x9f84cd87,
         0x7a584718, 0x7408da17, 0xbc9f9abc, 0xe94b7d8c, 0xec7aec3a,
         0xdb851dfa, 0x63094366, 0xc464c3d2, 0xef1c1847, 0x3215d908,
         0xdd433b37, 0x24c2ba16, 0x12a14d43, 0x2a65c451, 0x50940002,
         0x133ae4dd, 0x71dff89e, 0x10314e55, 0x81ac77d6, 0x5f11199b,
         0x043556f1, 0xd7a3c76b, 0x3c11183b, 0x5924a509, 0xf28fe6ed,
         0x97f1fbfa, 0x9ebabf2c, 0x1e153c6e, 0x86e34570, 0xeae96fb1,
         0x860e5e0a, 0x5a3e2ab3, 0x771fe71c, 0x4e3d06fa, 0x2965dcb9,
         0x99e71d0f, 0x803e89d6, 0x5266c825, 0x2e4cc978, 0x9c10b36a,
         0xc6150eba, 0x94e2ea78, 0xa5fc3c53, 0x1e0a2df4, 0xf2f74ea7,
         0x361d2b3d, 0x1939260f, 0x19c27960, 0x5223a708, 0xf71312b6,
         0xebadfe6e, 0xeac31f66, 0xe3bc4595, 0xa67bc883, 0xb17f37d1,
         0x018cff28, 0xc332ddef, 0xbe6c5aa5, 0x65582185, 0x68ab9802,
         0xeecea50f, 0xdb2f953b, 0x2aef7dad, 0x5b6e2f84, 0x1521b628,
         0x29076170, 0xecdd4775, 0x619f1510, 0x13cca830, 0xeb61bd96,
         0x0334fe1e, 0xaa0363cf, 0xb5735c90, 0x4c70a239, 0xd59e9e0b,
         0xcbaade14, 0xeecc86bc, 0x60622ca7, 0x9cab5cab, 0xb2f3846e,
         0x648b1eaf, 0x19bdf0ca, 0xa02369b9, 0x655abb50, 0x40685a32,
         0x3c2ab4b3, 0x319ee9d5, 0xc021b8f7, 0x9b540b19, 0x875fa099,
         0x95f7997e, 0x623d7da8, 0xf837889a, 0x97e32d77, 0x11ed935f,
         0x16681281, 0x0e358829, 0xc7e61fd6, 0x96dedfa1, 0x7858ba99,
         0x57f584a5, 0x1b227263, 0x9b83c3ff, 0x1ac24696, 0xcdb30aeb,
         0x532e3054, 0x8fd948e4, 0x6dbc3128, 0x58ebf2ef, 0x34c6ffea,
         0xfe28ed61, 0xee7c3c73, 0x5d4a14d9, 0xe864b7e3, 0x42105d14,
         0x203e13e0, 0x45eee2b6, 0xa3aaabea, 0xdb6c4f15, 0xfacb4fd0,
         0xc742f442, 0xef6abbb5, 0x654f3b1d, 0x41cd2105, 0xd81e799e,
         0x86854dc7, 0xe44b476a, 0x3d816250, 0xcf62a1f2, 0x5b8d2646,
         0xfc8883a0, 0xc1c7b6a3, 0x7f1524c3, 0x69cb7492, 0x47848a0b,
         0x5692b285, 0x095bbf00, 0xad19489d, 0x1462b174, 0x23820e00,
         0x58428d2a, 0x0c55f5ea, 0x1dadf43e, 0x233f7061, 0x3372f092,
         0x8d937e41, 0xd65fecf1, 0x6c223bdb, 0x7cde3759, 0xcbee7460,
         0x4085f2a7, 0xce77326e, 0xa6078084, 0x19f8509e, 0xe8efd855,
         0x61d99735, 0xa969a7aa, 0xc50c06c2, 0x5a04abfc, 0x800bcadc,
         0x9e447a2e, 0xc3453484, 0xfdd56705, 0x0e1e9ec9, 0xdb73dbd3,
         0x105588cd, 0x675fda79, 0xe3674340, 0xc5c43465, 0x713e38d8,
         0x3d28f89e, 0xf16dff20, 0x153e21e7, 0x8fb03d4a, 0xe6e39f2b,
         0xdb83adf7},
        {
            /* S2 */
            // ... (initialization values)
        },
        {
            /* S3 */
            // ... (initialization values)
        }};

    void initialize()
    {
        P = P_init;
        S = S_init;
    }

    uint32_t F(uint32_t x)
    {
        return ((S[0][x >> 24] + S[1][(x >> 16) & 0xff]) ^ S[2][(x >> 8) & 0xff]) + S[3][x & 0xff];
    }

    void encryptBlock(uint32_t &left, uint32_t &right)
    {
        for (int i = 0; i < 16; i++)
        {
            left ^= P[i];
            right ^= F(left);
            swap(left, right);
        }
        swap(left, right);
        right ^= P[16];
        left ^= P[17];
    }

    void decryptBlock(uint32_t &left, uint32_t &right)
    {
        for (int i = 17; i > 1; i--)
        {
            left ^= P[i];
            right ^= F(left);
            swap(left, right);
        }
        swap(left, right);
        right ^= P[1];
        left ^= P[0];
    }

    void padString(string &str)
    {
        size_t originalLength = str.size();
        size_t paddedLength = ((originalLength + 7) / 8) * 8; // Ensure padding to the next multiple of 8
        str.resize(paddedLength, 0);                          // Add null bytes as padding
    }

public:
    Blowfish(const string &key)
    {
        initialize();
        // Perform key expansion
        keyExpansion(key);
    }

    void keyExpansion(const string &key)
    {
        // Key expansion algorithm
        size_t keyLength = key.size();
        size_t keyIndex = 0;

        for (size_t i = 0; i < P.size(); i++)
        {
            uint32_t data = 0x00000000;
            for (size_t j = 0; j < 4; j++)
            {
                data = (data << 8) | key[keyIndex];
                keyIndex = (keyIndex + 1) % keyLength;
            }
            P[i] ^= data;
        }

        uint32_t left = 0x00000000;
        uint32_t right = 0x00000000;

        for (size_t i = 0; i < P.size(); i += 2)
        {
            encryptBlock(left, right);
            P[i] = left;
            P[i + 1] = right;
        }

        for (size_t i = 0; i < S.size(); i++)
        {
            for (size_t j = 0; j < S[i].size(); j += 2)
            {
                encryptBlock(left, right);
                S[i][j] = left;
                S[i][j + 1] = right;
            }
        }
    }

    string encrypt(const string &data)
    {
        string paddedData = data;
        padString(paddedData);
        for (size_t i = 0; i < paddedData.size(); i += 8)
        {
            uint32_t left = 0, right = 0;
            memcpy(&left, &paddedData[i], sizeof(uint32_t));
            memcpy(&right, &paddedData[i + 4], sizeof(uint32_t));
            encryptBlock(left, right);
            memcpy(&paddedData[i], &left, sizeof(uint32_t));
            memcpy(&paddedData[i + 4], &right, sizeof(uint32_t));
        }
        return paddedData;
    }

    string decrypt(const string &data)
    {
        string decryptedData = data;
        for (size_t i = 0; i < decryptedData.size(); i += 8)
        {
            uint32_t left = 0, right = 0;
            memcpy(&left, &decryptedData[i], sizeof(uint32_t));
            memcpy(&right, &decryptedData[i + 4], sizeof(uint32_t));
            decryptBlock(left, right);
            memcpy(&decryptedData[i], &left, sizeof(uint32_t));
            memcpy(&decryptedData[i + 4], &right, sizeof(uint32_t));
        }
        return decryptedData;
    }
};

int main()
{
    string key = "examplekey";
    Blowfish blowfish(key);

    string plaintext = "exampledata";
    string encrypted = blowfish.encrypt(plaintext);

    cout << "Encrypted: ";
    for (unsigned char c : encrypted)
    {
        cout << hex << setw(2) << setfill('0') << (int)c;
    }
    cout << endl;

    string decrypted = blowfish.decrypt(encrypted);
    cout << "Decrypted: " << decrypted << endl;

    return 0;
}
