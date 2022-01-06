#include <Windows.h>
#include <iostream>
#include "mem.h"


DWORD WINAPI HackThread(HMODULE hModule) 
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "CONOUT$", "w", stdout);
	std::cout << "Internal DLL" << std::endl;
	// system("pause");

	uintptr_t moduleBase = (uintptr_t)GetModuleHandle(NULL);

	while (true)
	{
		if ((GetAsyncKeyState(VK_END) & 1)) {
			break;
		}

		uintptr_t pointAddr = mem::FindDMAAddy(moduleBase + 0x131EDC, { 0x68 });
		int* point = (int*)pointAddr;
		*point = 9999999;

		Sleep(500);
	}

	fclose(f);
	FreeConsole();
	FreeLibraryAndExitThread(hModule, 0);
	return 0;

}


BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)HackThread, hModule,0,nullptr));
	}
	else if (dwReason == DLL_PROCESS_DETACH)
	{
		
	}
	return TRUE;
}