#include "includes.h"
#include <cstdlib>
#include "Windows.h"

//#define SALT_LENGTH 4
//string salt = "skar";


std::string __string_to_hex(const std::string& in) {
    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    for (size_t i = 0; in.length() > i; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
    }

    return ss.str();
}

std::string __get_username() {
    char* user = nullptr;
    size_t len = 0;
    if (_dupenv_s(&user, &len, "USERNAME") == 0 && user != nullptr) {
        std::string username(user);
        free(user);
        return username;
    }
}
