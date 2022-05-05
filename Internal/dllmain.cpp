#include <Windows.h>
#include <iostream>

DWORD WINAPI MainThread(HMODULE hModule) {
	DWORD moduleBase = (DWORD)GetModuleHandle("ConsoleApplication2.exe");
	DWORD cracked = *(DWORD*)(moduleBase + 0x1057);
	*(DWORD*)(moduleBase + 0x1057) = 2088961908;
	//cracked!
	FreeLibraryAndExitThread(hModule, 0);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return true;
}