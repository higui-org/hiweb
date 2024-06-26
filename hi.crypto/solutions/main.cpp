#include <iostream>
#include <cstring>

#include "SHA256.h"

bool IsBigEndian() {
    union {
        uint32_t i;
        char c[4];
    } bint = {0x01020304};

    return bint.c[0] == 1; 
}

/*
int main() {
    if (IsBigEndian()) {
        std::cout << "System is Big Endian" << std::endl;
    } else {
        std::cout << "System is Little Endian" << std::endl;
    }
    return 0;
}
*/


/*
int main() {
    const char* message = "hello world";
    unsigned char buffer[32];
    unsigned char digest[32];

    // Initialize the buffer with zeros
    std::memset(buffer, 0, sizeof(buffer));
    std::memset(digest, 0, sizeof(digest));

    std::cout << "Initializing SHA256..." << std::endl;
    SHA256_Init(buffer);

    std::cout << "Updating SHA256 with message: " << message << std::endl;
    SHA256_Update(reinterpret_cast<const unsigned char*>(message), std::strlen(message), buffer);

    std::cout << "Finalizing SHA256..." << std::endl;
    SHA256_Final(buffer, digest);

    std::cout << "SHA256 Digest: ";
    SHA256_Print(digest, 32);

    return 0;
}*/

int main() {
    uint8_t hash[32];
    SHA256_CTX ctx;
    const char *text = "Hello, world!wegewkpgewkh[pewkh[perohpjeopgrefogiewf0igw-ifg-=wgie-g==qewgoe";

    sha256_init(&ctx);
    sha256_update(&ctx, (const uint8_t*)text, strlen(text));
    sha256_final(&ctx, hash);

    printf("SHA-256 hash: ");
    for (int i = 0; i < 32; ++i)
        printf("%02x", hash[i]);
    printf("\n");

    return 0;
}