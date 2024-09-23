#include "salt_and_hash.h"
#include <algorithm>
#include <cctype>    


#define SALT_LENGTH 4
string salt = "skar";

string xorTransform(const string& hexString, const string& key) {
    string transformedHex = hexString;
    size_t keySize = key.size();
    for (size_t i = 0; i < transformedHex.size(); ++i) {
        transformedHex[i] ^= key[i % keySize];
    }
    return transformedHex;
}

string aes_encrypt(const string& plaintext, const CryptoPP::byte key[AES::DEFAULT_KEYLENGTH], const CryptoPP::byte iv[AES::BLOCKSIZE]) {
    std::string plaintext_salted = salt + plaintext;

    string ciphertext;
    try {
        CBC_Mode<AES>::Encryption encryption(key, AES::DEFAULT_KEYLENGTH, iv);
        StringSource(plaintext_salted, true, new StreamTransformationFilter(encryption, new StringSink(ciphertext)));
    }
    catch (const Exception& ex) {
    }

    string encryptedHex;
    StringSource(ciphertext, true, new HexEncoder(new StringSink(encryptedHex)));

    string transformedHex = xorTransform(encryptedHex, salt);

    for (char& c : transformedHex) {
        c = toupper(c);
    }

    return transformedHex;
}

string aes_decrypt(const string& transformedHex, const CryptoPP::byte key[AES::DEFAULT_KEYLENGTH], const CryptoPP::byte iv[AES::BLOCKSIZE]) {
    string reversedHex = xorTransform(transformedHex, salt);

    string ciphertext;
    StringSource(reversedHex, true, new HexDecoder(new StringSink(ciphertext)));

    string decryptedtext;
    try {
        CBC_Mode<AES>::Decryption decryption(key, AES::DEFAULT_KEYLENGTH, iv);
        StringSource(ciphertext, true, new StreamTransformationFilter(decryption, new StringSink(decryptedtext)));
    }
    catch (const Exception& ex) {
    }

    decryptedtext = decryptedtext.substr(salt.size());

    return decryptedtext;
}