//
// Created by lulu on 17-10-17.
//


#include <rsa.h>
#include <base64.h>
#include <openssl/pem.h>
#include <iostream>

RSAEncrypt::RSAEncrypt() {}

RSAEncrypt::~RSAEncrypt() {}

std::string RSAEncrypt::getPublicKey(int buildType) {

    std::string result;
    switch (buildType) {
        case 1:
            result = DEV_PUBLIC_KEY;
            break;
        case 2:
            result = QA_PUBLIC_KEY;
            break;
        case 3:
            result = PRO_PUBLIC_KEY;
            break;
        default:
            result = PRO_PUBLIC_KEY;
    }
    return result;
}

RSA *RSAEncrypt::createRSA(std::string key, int flag) {
    int nPublicKeyLen = (int) key.size();      //strPublicKey为base64编码的公钥字符串
    for (int i = 64; i < nPublicKeyLen; i += 64) {
        if (key[i] != '\n') {
            key.insert(i, "\n");
        }
        i++;
    }
    key.insert(0, "-----BEGIN PUBLIC KEY-----\n");
    key.append("\n-----END PUBLIC KEY-----\n");
    char *chPublicKey = const_cast<char *>(key.c_str());
    RSA *rsa = NULL;
    BIO *keybio;
    keybio = BIO_new_mem_buf(chPublicKey, -1);
    if (keybio == NULL) {
        printf("Failed to create key BIO");
        return 0;
    }

    if (flag)
        rsa = PEM_read_bio_RSA_PUBKEY(keybio, &rsa, NULL, NULL);
    else
        rsa = PEM_read_bio_RSAPrivateKey(keybio, &rsa, NULL, NULL);
    BIO_free_all(keybio);
    if (rsa == NULL)
        printf("Failed to create RSA");
    return rsa;
}

std::string RSAEncrypt::encrypt(std::string plain, std::string key) {

    int rsa_len;
    RSA *rsa = createRSA(key, 1);
    if (rsa == NULL) {
        return NULL;
    }
    rsa_len = RSA_size(rsa);
    char *encrypt = NULL;
    encrypt = new char[rsa_len + 1];
    int flag = RSA_public_encrypt((int) plain.length(), (const unsigned char *) plain.c_str(),
                                  (unsigned char *) encrypt, rsa, RSA_PKCS1_PADDING);
    if (flag == -1) {
        std::cout << "Encrypt failed!" << std::endl;
        delete[] encrypt;
        RSA_free(rsa);
        return NULL;
    }

    std::vector<byte> ve;
    std::string tmp = (char*)encrypt;
    ve.resize(tmp.size());
    ve.assign(tmp.begin(), tmp.end());
    std::string result = Base64::encode(ve);
    delete[] encrypt;
    RSA_free(rsa);
    return result;
}

std::string RSAEncrypt::decrypt(std::string cipher, std::string key) {

    int rsa_len;
    RSA *rsa = createRSA(key, 1);
    if (rsa == NULL) {
        return NULL;
    }
    cipher = "ATkjNKdQRIgzvjbCXNYhKj0o3OWqgi+8i6is5PudJns0E+tGNzFwEQ++yfaq9Ra1Z1d98QKLfzvXlQDbxN7bhAfR5n0IjlG6b73XIOPhXOiEJEKvnn8BUb0cQWuW130OunV+ujnOuzEENY8/nMbpqUlRxV56d3PY9MDF+Y8hikM=";
    std::vector<byte> src_v = Base64::decode(cipher);
    std::string src_str = std::string(src_v.begin(), src_v.end());
    rsa_len = RSA_size(rsa);
    char *decrypt = NULL;
    decrypt = new char[16];
    int flag = RSA_public_decrypt((int) src_str.size(), (const unsigned char *) src_str.c_str(),
                                  (unsigned char *) decrypt, rsa, RSA_PKCS1_PADDING);
    if (flag == -1) {
        std::cout << "Encrypt failed!" << std::endl;
        delete[] decrypt;
        RSA_free(rsa);
        return NULL;
    }
    std::string result = decrypt;
    delete[] decrypt;
    RSA_free(rsa);
    return result;
}
