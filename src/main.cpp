#include <vector>
#include <list>
#include <array>
#include <string>
#include <iostream>
#include "hiweb/SHA2.h"

template<typename InputIterator>
void printDigest(InputIterator begin, InputIterator end)
{
    hiweb::SHA256 s;
    std::vector<unsigned char> encrypted = s.Encrypt(begin, end);
    std::cout << "Encrypted message: " <<  s.ToHexString(encrypted) << std::endl;
}

int main() 
{
    // Example containers
    std::vector<char> vecChar = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};
    std::vector<unsigned char> vecUChar(vecChar.begin(), vecChar.end());
    std::list<char> listChar(vecChar.begin(), vecChar.end());
    std::list<unsigned char> listUChar(vecUChar.begin(), vecUChar.end());
    std::array<char, 11> arrayChar = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};
    std::array<unsigned char, 11> arrayUChar = {'H', 'e', 'l', 'l', 'o', ' ', 'W', 'o', 'r', 'l', 'd'};
    std::string str = "Hello World";

    // Calling printDigest for each type
    printDigest(vecChar.begin(), vecChar.end());
    printDigest(vecUChar.begin(), vecUChar.end());
    printDigest(listChar.begin(), listChar.end());
    printDigest(listUChar.begin(), listUChar.end());
    printDigest(arrayChar.begin(), arrayChar.end());
    printDigest(arrayUChar.begin(), arrayUChar.end());
    printDigest(str.begin(), str.end());

    /*
    OUTPUT:
    Encrypted message: a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e
    Encrypted message: a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e
    Encrypted message: a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e
    Encrypted message: a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e
    Encrypted message: a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e
    Encrypted message: a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e
    Encrypted message: a591a6d40bf420404a011733cfb7b190d62c65bf0bcda32b57b277d9ad9f146e
    */

    return 0;
}