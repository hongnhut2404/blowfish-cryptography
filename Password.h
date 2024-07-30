#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <random>
#include <chrono>
#include <unordered_map>
using namespace std;

string generateRandomSalt(size_t length);
string generateSalt(size_t length);
string generateHash(const string &password, const string &salt);
void storePassword(unordered_map<string, pair<string, string>> &passwordStorage, const string &username, const string &password);
bool verifyPasswordChange(const unordered_map<string, pair<string, string>> &passwordStorage, const string &username, const string &oldPassword, const string &newPassword);
bool verifyPassword(const string &password);
void clearInputBuffer();