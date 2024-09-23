#include "includes.h"
#include <cstdlib>
#include "Windows.h"
#include <ctime>
#include <process.h> 
#include <random>
#include <wincrypt.h>

char compile_time[] = __TIME__;

//const CryptoPP::SecByteBlock __gen_key() {
//    constexpr int keyLength = CryptoPP::AES::DEFAULT_KEYLENGTH;
//    constexpr char compile_time[] = __TIME__;
//    time_t current_time = std::time(nullptr);
//    int process_id = _getpid(); 
//    std::string entropy_source = compile_time + std::to_string(current_time) + std::to_string(process_id);
//    CryptoPP::SHA256 hash;
//    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];
//    hash.CalculateDigest(digest, reinterpret_cast<const CryptoPP::byte*>(entropy_source.c_str()), entropy_source.length());
//
//    CryptoPP::SecByteBlock key(keyLength);
//    for (int i = 0; i < keyLength; ++i) {
//        key[i] = digest[i] ^ digest[(i + keyLength) % CryptoPP::SHA256::DIGESTSIZE];
//    }
//
//    return key;
//}


CryptoPP::SecByteBlock __gen_key() {
    constexpr int __length = CryptoPP::AES::DEFAULT_KEYLENGTH;
    CryptoPP::SecByteBlock key(__length);

    HCRYPTPROV hCryptProv = 0;
    if (!CryptAcquireContext(&hCryptProv, nullptr, nullptr, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        return key;
    }

    if (!CryptGenRandom(hCryptProv, __length, key.begin())) {
    }

    CryptReleaseContext(hCryptProv, 0);
    return key;
}


CryptoPP::SecByteBlock __gen_iv() {
    const size_t AES_BLOCK_SIZE = 16;
    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::SecByteBlock iv(AES_BLOCK_SIZE);
    prng.GenerateBlock(iv, iv.size());
    return iv;
}