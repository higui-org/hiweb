#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>
#include "SHA256.h"

#define TEXT_LENGTH 1000

int main() {
    uint8_t hash[32];
    f::SHA256_CTX ctx;
    char text[TEXT_LENGTH + 1];
    memset(text, 'a', TEXT_LENGTH);
    text[TEXT_LENGTH] = '\0';
    clock_t start, end;
    double cpu_time_used;
    double data_size_mb = (double)TEXT_LENGTH * 10000000 / (1024 * 1024);

    // Measure time for custom SHA-256 implementation
    start = clock();
    for (int i = 0; i < 1000000; ++i) {
        f::sha256_init(&ctx);
        f::sha256_update(&ctx, (const uint8_t*)text, strlen(text));
        f::sha256_final(&ctx, hash);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Custom SHA-256 time: %f seconds\n", cpu_time_used);
    printf("Custom SHA-256 speed: %f MB/sec\n", data_size_mb / cpu_time_used);

    // Measure time for OpenSSL SHA-256 implementation
    start = clock();
    for (int i = 0; i < 1000000; ++i) {
        SHA256((const unsigned char*)text, strlen(text), hash);
    }
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("OpenSSL SHA-256 time: %f seconds\n", cpu_time_used);
    printf("OpenSSL SHA-256 speed: %f MB/sec\n", data_size_mb / cpu_time_used);

    return 0;
}