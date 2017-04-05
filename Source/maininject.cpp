#include <iostream>
#include <Windows.h>

using namespace std;

HANDLE GetProcessHandle(const char* procName);

int main() {
    string title = "Starcraft II";
    HWND window = FindWindow(0, title.c_str());
    HANDLE hProcess;
    DWORD pid;

    int minerals;
    int moreminerals = 10000;

    if (!window) {
        cout << "Window not found\n\n";
    } else {
        GetWindowThreadProcessId(window, &pid);

        cout << "Found: " << pid << "\n\n";

        hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

        if (!hProcess) {
            cout << "Error: cannot open process\n\n";
        } else {
            cout << "Process opened\n\n";

            if(!ReadProcessMemory(hProcess, (void*)0x026A0448, (void*)&minerals, sizeof(minerals), NULL))
            {
                cout << "Error: Failed to read memory\n\n";
            }

        }
    }
    CloseHandle(hProcess);
    cin.get();
    return 0;
}