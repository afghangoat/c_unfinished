#include <stdio.h>
#include <windows.h>

//dll code
BOOL APIENTRY DllMain(HMODULE hmod, DWORD reason, LPVOID reserved){
	switch(reason){
		case DLL_PROCESS_ATTACH:
			MessageBoxA("DLL attached!","WARNING",MB_ICONEXCLAMATION);
			break;
		case DLL_PROCESS_DETACH:
			MessageBoxA("DLL detached!","WARNING",MB_ICONEXCLAMATION);
			break;
		case DLL_THREAD_ATTACH:
			MessageBoxA("DLL thread attached!","WARNING",MB_ICONEXCLAMATION);
			break;
		case DLL_THREAD_DETACH:
			MessageBoxA("DLL thread detached!","WARNING",MB_ICONEXCLAMATION);
			break;
	}
	return TRUE;
}

DWORD WINAPI thread_func(LPVOID lpParam){
	printf("Thread is running.");
	return 0;
}

int main(int argc, char** argv){
	PCSTR path_to_dll=argv[1];
	HINSTANCE DLL_to_add = LoadLibraryA(argv[1]);
	if(DLL_to_add==NULL){
		printf("DLL not found or failed to load!");
		return 1;
	}
	
	HANDLE handler_thread = CreateThread(NULL,0,thread_func,NULL,0,NULL);
	if(handler_thread==NULL){
		printf("Thread creation failed!");
		return 1;
	}
	
	WaitForSingleObject(handler_thread,INFINITE);
	CloseHandle(handler_thread);
	FreeLibrary(DLL_to_add);
	return 0;
}