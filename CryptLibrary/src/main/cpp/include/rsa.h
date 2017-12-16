//
// Created by lulu on 17-10-17.
//

#ifndef CRYPTLIB_RSA_H
#define CRYPTLIB_RSA_H
//dev
#define DEV_PUBLIC_KEY "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCH9MuHj3Bg2o3f/W/MkY4WMTPvG9YsWLm2QeB3A0pNt6tcrFSUKbaBJ5xbb6ypgv8D/cVuIjMiyTWSAXNUTQ0vxQUFfZOV8OZSPCFnGSJO2TiVmZZ4yqWeZMY00QL04CZabiJCn1xqVeOm4kmHvUwmmRr2WlW16bZT9GPPDTEuuQIDAQAB"
//qa
#define QA_PUBLIC_KEY ""//TODO:测试公钥
//pro
#define PRO_PUBLIC_KEY ""//TODO:生产公钥


#include <string>
#include <openssl/ossl_typ.h>

class RSAEncrypt {

public:

    RSAEncrypt();

    ~RSAEncrypt();

    std::string getPublicKey(int buildType);

    std::string encrypt(std::string plain, std::string key);

    std::string decrypt(std::string cipher, std::string key);

private:

    RSA *createRSA(std::string key, int flag);

};


#endif //CRYPTLIB_RSA_H
