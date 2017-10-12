#ifndef CRYPTLIB_BASE64_H
#define CRYPTLIB_BASE64_H


#include <string>

class Base64 {
public:

    std::string Encode(const unsigned char *Data, int DataByte);

    std::string Decode(const char *Data, int DataByte, int &OutByte);
};

#endif //CRYPTLIB_BASE64_H