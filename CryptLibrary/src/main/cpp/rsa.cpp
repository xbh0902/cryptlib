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
    int nPublicKeyLen = (int) key.size();//key为base64编码的公钥字符串
    for (int i = 64; i < nPublicKeyLen; i += 64) {
        if (key[i] != '\n') {
            key.insert((unsigned long) i, "\n");
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
        return NULL;
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
    char *encrypt = new char[rsa_len + 1];
    memset(encrypt, 0, (size_t) (rsa_len + 1));//初始化内存
    int flag = RSA_public_encrypt((int) plain.length(), (const unsigned char *) plain.c_str(),
                                  (unsigned char *) encrypt, rsa, RSA_PKCS1_PADDING);
    if (flag == -1) {
        std::cout << "Encrypt failed!" << std::endl;
        delete[] encrypt;
        RSA_free(rsa);
        return NULL;
    }

    std::vector<byte> ve;
    std::string tmp = std::string(encrypt, (unsigned long) flag);
    ve.resize(tmp.size());
    ve.assign(tmp.begin(), tmp.end());
    std::string result = Base64::encode(ve);
    delete[] encrypt;
    RSA_free(rsa);
    return result;
}

std::string RSAEncrypt::decrypt(std::string cipher, std::string key) {

    std::string result;
    RSA *rsa = createRSA(key, 1);
    if (rsa == NULL) {
        return NULL;
    }
    std::vector<byte> src_v = Base64::decode(cipher);
    std::string src_str = std::string(src_v.begin(), src_v.end());
    int len = RSA_size(rsa);
    char *decrypt = new char[len + 1];
    memset(decrypt, 0, (size_t) (len + 1));//初始化内存
    int rlen = RSA_public_decrypt((int) src_str.size(), (const unsigned char *) src_str.c_str(),
                                  (unsigned char *) decrypt, rsa, RSA_PKCS1_PADDING);
    if (rlen == -1) {
        std::cout << "Encrypt failed!" << std::endl;
        delete[] decrypt;
        RSA_free(rsa);
        return NULL;
    }
    result = std::string(decrypt, (unsigned long) rlen);
    RSA_free(rsa);
    delete[] decrypt;
    return result;
}
