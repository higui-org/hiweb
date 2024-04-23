/**
 * @file SHA2.h
 * @brief Contains the declaration of the SHA2 class and its derived classes.
 * @see https://en.wikipedia.org/wiki/Cryptographic_algorithm
 * @see https://en.wikipedia.org/wiki/Cryptographic_hash_function
 * @see https://en.wikipedia.org/wiki/Cryptographic_primitive
 * @see https://en.wikipedia.org/wiki/Cryptographic_protocol
 * @see https://en.wikipedia.org/wiki/Cryptographic_software
 * @see https://en.wikipedia.org/wiki/Cryptographic_engine
 * @see https://en.wikipedia.org/wiki/Cryptographic_key
 * @see https://en.wikipedia.org/wiki/Cryptographic_nonce
 *
 * The CryptoAlgorithm class is an abstract base class that provides the interface for cryptographic algorithms.
 * The SHA256 class is a concrete implementation of the SHA-256 algorithm.
 * 
 * Copyright (C) 2024 setbe <max@lafk.eu>
*/

#ifndef HIWEB_SHA2_H
#define HIWEB_SHA2_H

#include <string>
#include <sstream>
#include <vector>
#include <array>
#include <memory>

namespace hiweb 
{
/**
 * @brief The base class for cryptographic algorithms.
 * @details This class provides the interface for cryptographic algorithms.
 * It defines the methods that must be implemented by derived classes.
 * 
 * About the class:
 * - The class is an abstract base class
 * - The class provides the interface for cryptographic algorithms
 * - The class defines the methods that must be implemented by derived classes
 * - The class stores the message to be processed
 * - The class provides a utility method to convert data to a hexadecimal string
 * - The class provides a virtual destructor
 * - The class is not copyable or movable
 */
class SHA2
{
protected:

    std::vector<unsigned char> message; ///< The message to be processed


    /**
     * @brief Initializes the cryptographic algorithm.
     * @details This method initializes the cryptographic algorithm.
     * @param message The message in bytes to be processed.
     * It sets the initial state of the algorithm.
     * @see https://en.wikipedia.org/wiki/Initialization_vector
    */
    virtual void Initialize(const std::vector<unsigned char>& message) noexcept = 0;


    /**
     * @brief Pads the message.
     * @details This method pads the message to a multiple of the block size.
     * It adds padding bits to the message to ensure that the message length is a multiple of the block size.
     * @see https://en.wikipedia.org/wiki/Padding_(cryptography)
    */
    virtual void Pad() noexcept = 0;


    /**
     * @brief Compresses the message.
     * @param block The message block to compress.
     * @details This method compresses the message.
     * It processes the message blocks to produce the final hash value.
     * @see https://en.wikipedia.org/wiki/Compression_function
    */
    virtual void Compress(const std::vector<unsigned char>& block) noexcept = 0;


    /**
     * @brief Finalizes the message.
     * @details This method finalizes the message.
     * It produces the final hash value from the compressed message blocks.
     * @see https://en.wikipedia.org/wiki/Finalization
    */
    virtual std::vector<unsigned char> Finalize() const noexcept = 0;


public:

    // Virtual destructor
    virtual ~SHA2() noexcept = default;


    /**
     * @brief Encrypts the message.
     * @details Encrypt for containers containing unsigned char
     * @param begin The iterator to the beginning of the message.
     * @param end The iterator to the end of the message.
     * @return The encrypted message.
     * @see https://en.wikipedia.org/wiki/Encryption
    */
    template<typename InputIterator>
    std::vector<unsigned char> Encrypt(InputIterator begin, InputIterator end) noexcept
    {
        std::vector<unsigned char> data(begin, end);
        
        Initialize(data);
        Pad();
        size_t num_blocks = message.size() * 8 / 512;
        for (size_t i = 0; i < num_blocks; i++) 
        {
            std::vector<unsigned char> block(message.begin() + i * 64, message.begin() + (i + 1) * 64);
            Compress(block);
        }
        return Finalize();
    }



    /**
     * @brief Converts a vector of unsigned chars to a hexadecimal string representation.
     * @param data The vector of unsigned chars to convert.
     * @return The hexadecimal string representation of the input data.
     * @see https://en.wikipedia.org/wiki/Hexadecimal
     * @see https://en.wikipedia.org/wiki/Hexadecimal#Written_representation
     * @see https://en.wikipedia.org/wiki/Hexadecimal#Distinguishing_from_decimal
     * @see https://en.wikipedia.org/wiki/Hexadecimal#Syntax_that_is_always_Hex
     * @see https://en.wikipedia.org/wiki/Hexadecimal#Binary_conversion
     * @see https://en.wikipedia.org/wiki/Hexadecimal#Division-remainder_in_source_base
     * @see https://en.wikipedia.org/wiki/Hexadecimal#Tools_for_conversion
    */
    static std::string ToHexString(const std::vector<unsigned char>& data);
};




/**
 * @brief The SHA-2 algorithm factory.
 * @details This class provides a factory method to create SHA-2 algorithm instances.
 * The factory method creates instances of the SHA-2 algorithm based on the algorithm type.
 * @see https://en.wikipedia.org/wiki/Factory_method_pattern
 * 
*/
class SHA2Factory 
{
public:
    /**
     * @brief The SHA-2 algorithm type.
     * @details This enumeration defines the SHA-2 algorithm types.
     * The types correspond to the different SHA-2 variants.
     * @see https://en.wikipedia.org/wiki/SHA-2
     * @see https://en.wikipedia.org/wiki/SHA-2#Comparison_of_SHA_functions
     * @see https://en.wikipedia.org/wiki/SHA-2#Pseudocode
     * @see https://en.wikipedia.org/wiki/SHA-2#Test_vectors
     * @see https://en.wikipedia.org/wiki/SHA-2#Cryptanalysis_and_validation
    */
    enum class Type 
    {
        //SHA224,
        SHA256,
        //SHA384,
        //SHA512,
        //SHA512_224,
        //SHA512_256
    };

    static std::unique_ptr<SHA2> CreateSHA2(Type type);
};




/**
 * @brief SHA-256 implementation.
 * @details This class implements the SHA-256 algorithm.
 * About the algorithm:
 * - The algorithm works on 512-bit blocks
 * - The message is padded to a multiple of 512 bits
 * - The message is split into 512-bit blocks
 * - The message is processed in 64 32-bit words
 * - The algorithm uses 64 32-bit constants
 * - The algorithm useІs 8 32-bit initial hash values
 * 
 * @see https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf
 * @see https://en.wikipedia.org/wiki/SHA-2
 * @see https://csrc.nist.gov/publications/detail/fips/180/4/final
 * @see https://en.wikipedia.org/wiki/SHA-2#Pseudocode
*/
class SHA256 : public SHA2
{
private:

    std::vector<unsigned int> digest;   ///< The 8 32-bit initial hash values
    static constexpr unsigned int K[64]
{
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2}; ///< The 64 32-bit constants ///< The 64 32-bit constants

protected:
    // Initialize the SHA-256 algorithm
    void Initialize(const std::vector<unsigned char>& message) noexcept override;


    /**
     * @brief Pad the message.
     * @details This function pads the message to a multiple of 512 bits.
     * @see https://en.wikipedia.org/wiki/SHA-2#Pseudocode
     * @see https://en.wikipedia.org/wiki/SHA-2#Pre-processing
     * @see https://en.wikipedia.org/wiki/SHA-2#Padding
     * 
    */
    void Pad() noexcept override;


    /**
     * @brief Compress the message.
     * @details This function compresses the message.
     * @see https://en.wikipedia.org/wiki/SHA-2#Pseudocode
     * @see https://en.wikipedia.org/wiki/SHA-2#Compression_function
     * 
    */
    void Compress(const std::vector<unsigned char>& block) noexcept override;


    /**
     * @brief Finalize the message.
     * @details This function finalizes the message.
     * @see https://en.wikipedia.org/wiki/SHA-2#Pseudocode
     * @see https://en.wikipedia.org/wiki/SHA-2#Output
    */
    std::vector<unsigned char> Finalize() const noexcept override;


    /**
     * @brief Performs a right circular shift on the input value by a specified number of bits.
     * 
     * This function executes a right circular shift, ensuring that the shift value is 
     * constrained to a valid range [0, 31]. The bits that are shifted out 
     * on the right are re-introduced at the left end. This method is often used in cryptographic 
     * algorithms to distribute bits across the output effectively.
     *
     * @param value The unsigned integer to rotate.
     * @param shift The number of bits to shift to the right. The value is normalized to [0, 31].
     * @return The result of the circular shift operation.
     * @see https://en.wikipedia.org/wiki/Circular_shift#
     * @see https://en.wikipedia.org/wiki/Circular_shift#Implementing_circular_shifts
     * @see https://en.wikipedia.org/wiki/Circular_shift#Example
     * @see https://en.wikipedia.org/wiki/Circular_shift#Applications
     * @see https://en.wikipedia.org/wiki/Circular_shift#Implementations
    */
    static unsigned int RightRotate(unsigned int value, int shift) noexcept;
};


} // namespace 'hiweb'

#endif // HIWEB_SHA2_H