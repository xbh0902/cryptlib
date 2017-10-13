#include "base64.h"

const char *Base64::table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
byte Base64::rtable[123];

int trick = Base64::init_rtable();

std::string Base64::encode(const std::vector<byte> &bytes) {
    int len = (int) bytes.size();
    std::string str;
    for (int i = 0; i < len; i += 3) {
        byte b0 = bytes[i];
        byte b1 = (byte) ((i + 1 < len) ? bytes[i + 1] : 0);
        byte b2 = (byte) ((i + 2 < len) ? bytes[i + 2] : 0);
        str.push_back(table[b0 >> 2]);
        str.push_back(table[((b0 & 0x3) << 4) | (b1 >> 4)]);
        str.push_back(table[((b1 & 0xf) << 2) | (b2 >> 6)]);
        str.push_back(table[b2 & 0x3f]);
    }
    int slen = (int) str.length();
    if (len % 3 == 1) {
        str[slen - 1] = '=';
        str[slen - 2] = '=';
    } else if (len % 3 == 2) {
        str[slen - 1] = '=';
    }
    for (int i = line_width, j = 0; i < slen; i += line_width, j++) {
        str.insert((unsigned long) (i + j), "\n");
    }
    return str;
}

std::vector<byte> Base64::decode(const std::string &str) {
    int len = (int) str.length();
    std::vector<byte> result;
    for (int i = 0; i < len; i += 4) {
        byte c0 = rtable[(byte) str[i]];
        byte c1 = rtable[(byte) str[i + 1]];
        byte c2 = rtable[(byte) str[i + 2]];
        byte c3 = rtable[(byte) str[i + 3]];
        result.push_back((const unsigned char &) ((c0 << 2) | ((c1 >> 4) & 0x3)));
        result.push_back((const unsigned char &) ((c1 << 4) | ((c2 >> 2) & 0xf)));
        result.push_back((const unsigned char &) ((c2 << 6) | (c3 & 0x3f)));
        if (i + 4 < len && str[i + 4] == '\n') {
            i++;
        }
    }
    for (int i = len - 1, count = 0; i >= 0 && count < 2; i--) {
        if (str[i] == '\n') {
            continue;
        } else if (str[i] == '=') {
            result.pop_back();
            count++;
        } else {
            break;
        }
    }
    return result;
}

int Base64::init_rtable() {
    for (int i = 'A'; i <= 'Z'; i++) {
        rtable[i] = (byte) (i - 'A');
    }
    for (int i = 'a'; i <= 'z'; i++) {
        rtable[i] = (byte) (i - 'a' + 26);
    }
    for (int i = '0'; i <= '9'; i++) {
        rtable[i] = (byte) (i - '0' + 52);
    }
    rtable['+'] = 62;
    rtable['/'] = 63;
    return 0;
}