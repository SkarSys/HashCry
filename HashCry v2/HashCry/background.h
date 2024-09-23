#include <Windows.h>
#include <iostream>
#include <fstream>
#include "bytes.h"

//void __change_background() {
//    std::ofstream file("temp.jpg", std::ios::out | std::ios::binary);
//    file.write(reinterpret_cast<const char*>(monkey_background), 188588);
//    file.close();
//
//    // Set JPEG file as desktop wallpaper
//    SystemParametersInfoA(SPI_SETDESKWALLPAPER, 1, reinterpret_cast<void*>(const_cast<char*>("temp.jpg")), SPIF_UPDATEINIFILE);
//    //SystemParametersInfoW(SPI_SETDESKWALLPAPER, 1, "temp.png", SPIF_UPDATEINIFILE | SPIF_SENDCHANGE);
//    int res = SystemParametersInfo(SPI_SETDESKWALLPAPER, 0, path3, SPIF_UPDATEINIFILE);
//
//    // Delete temporary file
//  //  std::remove("temp.jpg");
//}
