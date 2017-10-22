#ifndef CRYPTLIB_AES_H
#define CRYPTLIB_AES_H

#include <string>
#include <cstring>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <omp.h>
#include "base64.h"

typedef unsigned char byte;

class AES {
public:
    static const int ENCRYPTION = 0;
    static const int DECRYPTION = 1;

    AES();

    void setKey(const byte *key);

    std::string encrypt(const std::string &text);

    std::vector<byte> encrypt(const std::vector<byte> &bytes);

    std::vector<byte> encrypt(const byte *bytes, int len);

    std::string decrypt(const std::string &text);

    std::vector<byte> decrypt(const std::vector<byte> &bytes);

    std::vector<byte> decrypt(const byte *bytes, int len);

private:
    static const int BLOCK_SIZE = 16; // bytes
    static const int ROUNDS = 11;
    static const byte SBOX[256];
    static const byte SBOX_INV[256];
    static const byte COEF[4];
    static const byte COEF_INV[4];
    static const byte RC[11];

    static void add_round_key(byte *block, const byte *key);

    static void sub_bytes(byte *block, int direction);

    static void shift_rows(byte *block, int direction);

    static void mix_columns(byte *block, int direction);

    static void expansion(const byte *key, byte *ekey);

    byte ekey[ROUNDS * BLOCK_SIZE];

    void encrypt_block(byte *text);

    void decrypt_block(byte *text);
};

void transpose(byte *block);

byte mul(byte a, byte b);

#endif // CRYPTLIB_AES_H