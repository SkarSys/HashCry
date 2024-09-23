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
#include "UI.h" // for menu and imgui shit
using namespace std;
using namespace CryptoPP;
namespace fs = std::filesystem;