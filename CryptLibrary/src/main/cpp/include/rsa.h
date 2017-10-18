//
// Created by lulu on 17-10-17.
//

#ifndef CRYPTLIB_RSA_H
#define CRYPTLIB_RSA_H
//dev
#define DEV_PUBLIC_KEY "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCH9MuHj3Bg2o3f/W/MkY4WMTPvG9YsWLm2QeB3A0pNt6tcrFSUKbaBJ5xbb6ypgv8D/cVuIjMiyTWSAXNUTQ0vxQUFfZOV8OZSPCFnGSJO2TiVmZZ4yqWeZMY00QL04CZabiJCn1xqVeOm4kmHvUwmmRr2WlW16bZT9GPPDTEuuQIDAQAB"
//qa
#define QA_PUBLIC_KEY "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCJNQEkAJLg+g9Enmu3LoClp/9KD0qQLHIxCcikYU298yIRIPH347WA/hueAxlLa+47V7WXsr44oIQgwRkK5lxVB2VqhoUflK6jOzVqqOxn7TXhVu3AfdvDL2fpCWLF3NOZ+VqSODRpKQF/Od0ihZukc0fKQCVQag1BobGh4iZg2wIDAQAB"
//pro
#define PRO_PUBLIC_KEY "MIGfMA0GCSqGSIb3DQEBAQUAA4GNADCBiQKBgQCY0+J08c1WvI3WJeVfEZ56EXvWmy3oP/4oWMbzA2DhcN87r8y+8uRvxV748UsMSHGLHBGDWp7iHTZCWwns/P5O49RBZsp5Zl4dl7U1gW2TAh6lWMWoV9hoCqe8aAKfw9MfW2tBhYZwIWEojNLtq39pn2sTOCL4xILMI7OIHonuFQIDAQAB"

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
