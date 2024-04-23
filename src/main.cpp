#include "hiweb/CryptoAlgorithm.h"

#include <string>
#include <iostream>

int main() 
{
    hiweb::SHA256 sha({'h', 'e', 'l', 'o'});
    
    std::vector<unsigned char> encrypted_bytes = sha.Encrypt();

    std::string res = sha.ToHexString(encrypted_bytes);

    std::cout << "Encrypted message: " << res << std::endl;
    return 0;
}