import struct

# Constants for SHA-256
K = [
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
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
]


# Initial hash values for SHA-256
H = [
    0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
    0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
]

def right_rotate(value, count):
    """
    Perform a right rotation on a 32-bit integer.
    
    Parameters:
    value (int): The integer value to rotate.
    count (int): The number of bits to rotate.
    
    Returns:
    int: The result of the right rotation.
    """
    return ((value >> count) | (value << (32 - count))) & 0xffffffff

def sha256_padding(data):
    """
    Apply SHA-256 padding to the input data.
    
    Parameters:
    data (bytes): The input data to pad.
    
    Returns:
    bytes: The padded data.
    """
    original_length = len(data) * 8
    data += b'\x80'
    while (len(data) * 8) % 512 != 448:
        data += b'\x00'
    
    length_bits = original_length.to_bytes(8, byteorder='big')
    data += length_bits
    return data

def sha256_compress(chunk, H):
    """
    Perform the SHA-256 compression function on a single 512-bit chunk.
    
    Parameters:
    chunk (bytes): The 512-bit chunk.
    H (list): The current hash value (8 32-bit integers).
    
    Returns:
    list: The updated hash value (8 32-bit integers).
    """
    def bytes_to_ints(bytes_seq):
        return [int.from_bytes(bytes_seq[i:i+4], byteorder='big') for i in range(0, len(bytes_seq), 4)]
    
    w = bytes_to_ints(chunk) + [0] * 48
    for i in range(16, 64):
        s0 = right_rotate(w[i-15], 7) ^ right_rotate(w[i-15], 18) ^ (w[i-15] >> 3)
        s1 = right_rotate(w[i-2], 17) ^ right_rotate(w[i-2], 19) ^ (w[i-2] >> 10)
        w[i] = (w[i-16] + s0 + w[i-7] + s1) & 0xffffffff
    
    a, b, c, d, e, f, g, h = H
    for i in range(64):
        s1 = right_rotate(e, 6) ^ right_rotate(e, 11) ^ right_rotate(e, 25)
        ch = (e & f) ^ (~e & g)
        temp1 = (h + s1 + ch + K[i] + w[i]) & 0xffffffff
        s0 = right_rotate(a, 2) ^ right_rotate(a, 13) ^ right_rotate(a, 22)
        maj = (a & b) ^ (a & c) ^ (b & c)
        temp2 = (s0 + maj) & 0xffffffff
        
        h = g
        g = f
        f = e
        e = (d + temp1) & 0xffffffff
        d = c
        c = b
        b = a
        a = (temp1 + temp2) & 0xffffffff
    
    return [
        (H[0] + a) & 0xffffffff,
        (H[1] + b) & 0xffffffff,
        (H[2] + c) & 0xffffffff,
        (H[3] + d) & 0xffffffff,
        (H[4] + e) & 0xffffffff,
        (H[5] + f) & 0xffffffff,
        (H[6] + g) & 0xffffffff,
        (H[7] + h) & 0xffffffff
    ]

def sha256(data: str):
    """
    Compute the SHA-256 hash of a given input string.
    
    Parameters:
    data (str): Input string to be hashed.
    
    Returns:
    str: The resulting SHA-256 hash as a hexadecimal string.
    """
    data = data.encode()
    data = sha256_padding(data)
    
    H_local = H[:]
    for i in range(0, len(data), 64):
        H_local = sha256_compress(data[i:i+64], H_local)
    
    return ''.join(f'{x:08x}' for x in H_local)

# Example usage
if __name__ == "__main__":

    # TRUE hash: 315f5bdb76d078c43b8ac0064e4a0164612b1fce77c869345bfc94c75894edd3
    input_data = "Hello, world!"

    # TRUE hash: dc3744ceb54e0e24eb9f658d80bc6612d1c90d8acf9688f0cd3758b3ff3c7fdb
    larger_input_data = "The quick brown fox jumps over the lazy dog. Extra data to make the input larger."

    hash_result = sha256(input_data)
    larger_hash_result = sha256(larger_input_data)
    print(f"input '{input_data}': {hash_result}")
    print(f"larger input: {larger_hash_result}")
