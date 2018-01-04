#ifndef CRYPTLIB_BASE64_H
#define CRYPTLIB_BASE64_H

#include <string>
#include <vector>

typedef unsigned char byte;

class Base64 {
public:
    static std::string encode(const std::vector<byte> &bytes);

    static std::vector<byte> decode(const std::string &str);

    static int init_rtable();

private:
    static int trick;
    static const int line_width = 76;
    static const char *table;
    static byte rtable[123];
};

#endif // CRYPTLIB_BASE64_H