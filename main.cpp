#include <iostream>
#include <windows.h>
#include <sstream>


void maxHealth(HANDLE hProcess, int* base_ptr);
void maxBullets(HANDLE hProcess, int* base_ptr);
void maxReload(HANDLE hProcess, int* base_ptr);

namespace offsets {
    int healthAddress = 0xEC;
    int rifleBulletsAddress = 0x140;
    int bagAddress = 0x11C;
}

int main(int argc, char* argv[]) {
    const intptr_t BASE_ADDRESS = 0x057E0A8; // ac_client.exe
    int* base_ptr = 0;

    HWND gameWindow = FindWindow(NULL, L"AssaultCube");
    DWORD windowProcess;

    GetWindowThreadProcessId(gameWindow, &windowProcess);

    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, 0, windowProcess);

    ReadProcessMemory(hProcess, (LPCVOID)BASE_ADDRESS, &base_ptr, sizeof(int*), NULL);

    std::cout << "--------------------------------------" << std::endl;
    std::cout          << "[TAB] - Maximize Life\n"
                       << "[F1] - Maximize Primary Ammo\n"
                       << "[F2] - Maximize Primary Reload Ammo\n";
    std::cout << "--------------------------------------" << std::endl;

    while (true) {
        if (GetAsyncKeyState(VK_TAB)) {
            maxHealth(hProcess, base_ptr);
        }
        else if (GetAsyncKeyState(VK_F1)) {
            maxBullets(hProcess, base_ptr);
        }
        else if (GetAsyncKeyState(VK_F2)) {
            maxReload(hProcess, base_ptr);
        }
    }

    CloseHandle(hProcess);
    return 0;
}

void maxHealth(HANDLE hProcess, int* base_ptr) {
    int* target_ptr = reinterpret_cast<int*>((intptr_t)base_ptr + ::offsets::healthAddress);
    int target_value = 0;
    int maxHealth = 9999;

    // Ler o valor no endereço alvo
    ReadProcessMemory(hProcess, target_ptr, &target_value, sizeof(int), NULL);

    // Alterar o valor no endereço alvo
    WriteProcessMemory(hProcess, target_ptr, &maxHealth, sizeof(int), NULL);
}

void maxBullets(HANDLE hProcess, int* base_ptr) {
    int* target_ptr = reinterpret_cast<int*>((intptr_t)base_ptr + ::offsets::rifleBulletsAddress);
    int target_value = 0;
    int maxBullets = 9999;

    // Ler o valor no endereço alvo
    ReadProcessMemory(hProcess, target_ptr, &target_value, sizeof(int), NULL);

    // Alterar o valor no endereço alvo
    WriteProcessMemory(hProcess, target_ptr, &maxBullets, sizeof(int), NULL);
}

void maxReload(HANDLE hProcess, int* base_ptr) {
    int* target_ptr = reinterpret_cast<int*>((intptr_t)base_ptr + ::offsets::bagAddress);
    int target_value = 0;
    int maxReload = 9999;

    // Ler o valor no endereço alvo
    ReadProcessMemory(hProcess, target_ptr, &target_value, sizeof(int), NULL);

    // Alterar o valor no endereço alvo
    WriteProcessMemory(hProcess, target_ptr, &maxBullets, sizeof(int), NULL);
}

