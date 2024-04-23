#include "hiweb/CryptoAlgorithm.h"
#include <iomanip>
#include <cstdint>

namespace hiweb
{

/**
 * Converts a vector of unsigned chars to a hexadecimal string representation.
 * 
 * @param data The vector of unsigned chars to convert.
 * @return The hexadecimal string representation of the input data.
 */
std::string CryptoAlgorithm::ToHexString(const std::vector<unsigned char>& data) 
{
    std::stringstream hexstream;
    hexstream << std::hex << std::setfill('0');
    for (auto byte : data) 
    {
        hexstream << std::setw(2) << static_cast<int>(byte);
    }
    return hexstream.str();
}

std::vector<unsigned char> CryptoAlgorithm::Encrypt() noexcept
{
    Initialize();
    Pad();
    Compress();
    return Finalize();
}

/**
 * Initializes the SHA256 algorithm by setting the initial digest and resizing the working array.
 */
void SHA256::Initialize() noexcept
{
    digest = 
    {
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };
        
    W.resize(64);
}

/**
 * Pads the message with '1' and '0' bits according to the SHA256 specification.
 */
void SHA256::Pad() noexcept
{
    // We keep the original length of the message in bits
    size_t original_length = message.size() * 8;

    // Adding '1' bit
    message.push_back(0x80); // add 1000 0000 in bytes

    // Adding '0' bits
    size_t current_length = (message.size() * 8) % 512;
    size_t pad_length = (current_length > 448) ? (512 + 448 - current_length) : (448 - current_length);

    for (size_t i = 0; i < pad_length / 8; i++) 
    {
        message.push_back(0x00);
    }

    // Adding the length of the message as a 64-bit number in big-endian format
    uint64_t length_bits = static_cast<uint64_t>(original_length);
    for (int i = 7; i >= 0; --i) 
    {
        message.push_back(static_cast<unsigned char>((length_bits >> (8 * i)) & 0xFF));
    }
}

/**
 * @brief Compresses the message using the SHA-256 algorithm.
 * 
 * This function takes the message stored in the `message` array and compresses it using the SHA-256 algorithm.
 * It converts the message bytes into 32-bit words for processing, expands the words, initializes eight working variables,
 * and performs the main cycle of operations. Finally, it updates the current hash value stored in the `digest` array.
 * 
 * @note This function assumes that the `message` and `digest` arrays have been properly initialized.
 * 
 * @note This function does not throw any exceptions.
 */
void SHA256::Compress() noexcept
{
    std::array<unsigned int, 64> words;
    // Convert message bytes into 32-bit words for processing
    for (int i = 0; i < 16; ++i) 
    {
        words[i] = (message[4 * i] << 24) | (message[4 * i + 1] << 16) | (message[4 * i + 2] << 8) | message[4 * i + 3];
    }

    // Expanding words
    for (int i = 16; i < 64; ++i) 
    {
        unsigned int s0 = RightRotate(words[i - 15], 7) ^ RightRotate(words[i - 15], 18) ^ (words[i - 15] >> 3);
        unsigned int s1 = RightRotate(words[i - 2], 17) ^ RightRotate(words[i - 2], 19) ^ (words[i - 2] >> 10);
        words[i] = words[i - 16] + s0 + words[i - 7] + s1;
    }

    // Initialization of eight working variables
    unsigned int a = digest[0];
    unsigned int b = digest[1];
    unsigned int c = digest[2];
    unsigned int d = digest[3];
    unsigned int e = digest[4];
    unsigned int f = digest[5];
    unsigned int g = digest[6];
    unsigned int h = digest[7];

    // Main cycle
    for (int i = 0; i < 64; ++i) 
    {
        unsigned int S1 = RightRotate(e, 6) ^ RightRotate(e, 11) ^ RightRotate(e, 25);
        unsigned int ch = (e & f) ^ ((~e) & g);
        unsigned int temp1 = h + S1 + ch + K[i] + words[i];
        unsigned int S0 = RightRotate(a, 2) ^ RightRotate(a, 13) ^ RightRotate(a, 22);
        unsigned int maj = (a & b) ^ (a & c) ^ (b & c);
        unsigned int temp2 = S0 + maj;

        h = g;
        g = f;
        f = e;
        e = d + temp1;
        d = c;
        c = b;
        b = a;
        a = temp1 + temp2;
    }

    // Update the current hash value
    digest[0] += a;
    digest[1] += b;
    digest[2] += c;
    digest[3] += d;
    digest[4] += e;
    digest[5] += f;
    digest[6] += g;
    digest[7] += h;
}

/**
 * Finalizes the SHA256 algorithm and returns the hash output.
 * 
 * @return The hash output as a vector of unsigned chars.
 */
std::vector<unsigned char> SHA256::Finalize() const noexcept 
{
    // Hash output
    std::vector<unsigned char> output;
    output.reserve(digest.size() * sizeof(unsigned int));
    for (auto value : digest) 
    {
        for (int i = 3; i >= 0; --i) 
        {
            output.push_back((value >> (8 * i)) & 0xFF);
        }
    }
    return output;
}

/**
 * 
 * Performs a right rotation of the given value by the specified shift amount.
 * 
 * @param value The value to rotate.
 * @param shift The number of bits to shift by.
 * @return The result of the right rotation.
 */
unsigned int SHA256::RightRotate(unsigned int value, int shift) noexcept
{
    // Normalize the shift to ensure it is within the range [0, 31]
    shift = shift % 32;  // Use modulo to confine the shift within [0, 31]
    if (shift < 0) {
        shift += 32;  // Adjust if the modulo result is negative
    }
    // Perform the right circular shift
    return (value >> shift) | (value << (32 - shift));
}

} // namespace 'hiweb'