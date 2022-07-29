#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <Windows.h>
#include <thread>
#include <tlhelp32.h>
#include <conio.h>


#define pswd "745896321"


void CheckExplorerRunning() {
	while (true) {
		std::this_thread::sleep_for(std::chrono::seconds(2));
		bool exists = false;
		PROCESSENTRY32 processEntry;
		processEntry.dwSize = sizeof(PROCESSENTRY32);

		HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

		if (Process32First(snapshot, &processEntry)) {
			while (Process32Next(snapshot, &processEntry)) {
				if (!_wcsicmp(processEntry.szExeFile, L"explorer.exe")) {
					exists = true;
					break;
				}
			}
		}
		CloseHandle(snapshot);
		
		if (exists == true) {
			system("taskkill /F /IM explorer.exe > nul");
		}
	}
}

int main() {
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
	HMENU hmenu = GetSystemMenu(hwnd, FALSE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	EnableMenuItem(hmenu, SC_CLOSE, MF_GRAYED);
	std::thread explorerIsRunning(CheckExplorerRunning);
	system("title HyperSecurity");
	system("taskkill /F /IM explorer.exe > nul");
	printf("Explorer has been killed.\n\r");
	char c,pswdInput[32];
	printf("Welcome to hyperSecurity\n\r");
	printf("Enter the security password: ");
	scanf("%s", &pswdInput);

	if (strcmp(pswdInput, pswd) == 0) {
		explorerIsRunning.detach();
		printf("Password correct! Starting explorer!\n\r");
		Sleep(1000);
		system("start %windir%/explorer.exe");
		exit(EXIT_SUCCESS);
	}
	else {
		explorerIsRunning.detach();
		printf("Password incorrect, restarting computer.\n\r");
		Sleep(1000);
		system("shutdown -r");
		exit(EXIT_SUCCESS);
	}


}