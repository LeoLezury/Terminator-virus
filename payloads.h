#include <Windows.h>
#include <math.h>
#include <string>
#include <iostream>
#include <string>
#include <Shlwapi.h>
#include <fstream>
#pragma comment(lib,"Shlwapi.lib")
#pragma  comment(lib,"WinMM.lib")
using namespace std;
HCRYPTPROV prov;
int random() {
	if (prov == NULL)
		if (!CryptAcquireContext(&prov, NULL, NULL, PROV_RSA_FULL, CRYPT_SILENT | CRYPT_VERIFYCONTEXT))
			ExitProcess(1);

	int out;
	CryptGenRandom(prov, sizeof(out), (BYTE *)(&out));
	return out & 0x7fffffff;
}
POINT mkp(int x, int y){
	POINT p;
	p.x = x;
	p.y = y;
	return p;
}
#define thread(name) DWORD WINAPI name(LPVOID lpParam)
#define rt(thrdname) CreateThread(NULL, 0, thrdname, NULL, 0, NULL);
DWORD WINAPI pat(LPVOID lpParameter){
	int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	for(;;){
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 50, 50, w - 100, h - 100, PATINVERT);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 100, 100, w - 200, h - 200, PATINVERT);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 150, 150, w - 300, h - 300, PATINVERT);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 200, 200, w - 400, h - 400, PATINVERT);
		SelectObject(hdc, CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		PatBlt(hdc, 250, 250, w - 500, h - 500, PATINVERT);
	}
	return 0;
}
DWORD WINAPI wave(LPVOID lpParameter){
	int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(hcdc, hBitmap);
	for(;;){
		StretchBlt(hcdc, 0, 0, w, h, hdc, 0, 0, w, h, SRCCOPY);
		int r = h / 2;
		for(int i = 0; i <= r; i += 5){
			int d = sqrt(float(2 * r * i - i * i));
			StretchBlt(hcdc, -d / 3, i, w, 5, hdc, 0, i, w, 5, SRCCOPY);
		}
		for(int i = 0; i <= r; i += 5){
			int d = sqrt(float(2 * r * (r - i) - (r - i) * (r - i)));
			StretchBlt(hcdc, -d / 3, i + r, w, 5, hdc, 0, i + r, w, 5, SRCCOPY);
		}
		StretchBlt(hdc, 0, 0, w, h, hcdc, 0, 0, w, h, SRCCOPY);
		Sleep(10);
	}
}
DWORD WINAPI _Ellipse(LPVOID lpParameter){
	int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	int i = 0;
	int n = 50;
	int x = random()%(w - 400);
	int y = random()%(h - 400);
	for(int cnt = 0;cnt < 50;cnt++){
		if(n >= 450){
			x = random()%(w - 400);
			y = random()%(h - 400);
			n = 50;
			i = 0;
			
		}
		HDC hcdc = CreateCompatibleDC(hdc);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, SRCCOPY);
		HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
		SelectObject(hcdc, hBitmap);
		BitBlt(hcdc, 0, 0, w, h, hdc, 0, 0, NOTSRCCOPY);
		HBRUSH hBrush = CreatePatternBrush(hBitmap);
		SelectObject(hdc, hBrush);
		for(; i <= n; i += 10){
			Ellipse(hdc, x-i, y-i, x+i, y+i);
			Sleep(20);
		}
		DeleteObject(hBrush);
		DeleteObject(hBitmap);
		n += 50;
	}
	return 0;
}
DWORD WINAPI Stretch(LPVOID lpParameter){
	int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	for(int i = 0;i < 1200;i++){
		int _w = random()%100+400,_h = random()%100+400;
		int x = random()%(w - _w),y = random()%(h - _h);
		StretchBlt(hdc, x + (5 - random()%10), y + (5 - random()%10), _w + (5 - random()%10), _h + (5 - random()%10), hdc, x, y, _w, _h, SRCCOPY);
		StretchBlt(hdc, x + (5 - random()%10), y + (5 - random()%10), _w + (5 - random()%10), _h + (5 - random()%10), hdc, x, y, _w, _h, SRCCOPY);
		StretchBlt(hdc, x + (5 - random()%10), y + (5 - random()%10), _w + (5 - random()%10), _h + (5 - random()%10), hdc, x, y, _w, _h, SRCCOPY);
	}
	return 0;
}
void _DrawError(bool x){
	int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
	int icnsz = GetSystemMetrics(SM_CXICON);
	HDC hdc = GetDC(NULL);
	POINT p;
	if(x){
		p = mkp(0, random()%h);
	}else{
		p = mkp(random()%w, 0);
	}
	for(;;){
		if(p.x >= w || p.y >= h){
			return;
		}
		DrawIcon(hdc, p.x, p.y, LoadIcon(NULL, IDI_ERROR));
		p.x += icnsz;
		p.y += icnsz;
		Sleep(50);
	}
	return;
}
DWORD WINAPI DrawError(LPVOID lpParameter){
	for(int i = 0;i < 30;i++){
		_DrawError(random()%2);
	}
	return 0;
}
DWORD WINAPI CopyCur(LPVOID lpParameter){
	int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	for(;;){
		CURSORINFO pci; 
		pci.cbSize = sizeof(pci);
		GetCursorInfo(&pci);
		for(int i = 1; i <= 20; i++)
			DrawIcon(hdc, random()%w, random()%h, pci.hCursor);
		Sleep(500);
	}
	return 0;
}
DWORD WINAPI Tunnel(LPVOID lpParameter){
	int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	for(int i = 0;i < 100;i++){
		POINT ps[3] = {mkp(0,h / 8), mkp(w - (w / 8),0), mkp(w / 8, h)};
		PlgBlt(hdc, ps, hdc, 0, 0, w, h, 0, 0, 0);
		Sleep(100);
	}
	return 0;
}
DWORD WINAPI Sound(LPVOID lpParameter){
	const int samples = 44100;

	WAVEFORMATEX fmt = { WAVE_FORMAT_PCM, 1, samples, samples, 1, 8, 0 };

	HWAVEOUT hwo;
	waveOutOpen(&hwo, WAVE_MAPPER, &fmt, NULL, NULL, CALLBACK_NULL);

	const int bufsize = samples * 30;
	char *wavedata = (char *)LocalAlloc(0, bufsize);

	WAVEHDR hdr = { wavedata, bufsize, 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hwo, &hdr, sizeof(hdr));

	for (;;) {
		int freq1 = 0, freq2 = 0, freq3 = 0;
		int sample1 = 0, sample2 = 0, sample3 = 0;
		for (int i = 0; i < bufsize; i++) {
			if (i % (int)(samples * 0.166) == 0) {
				freq1 = samples / (3580000.0 / (32 * ((random() % 41) * 10 + 200))) / 2;
				freq2 = samples / (3580000.0 / (32 * ((random() % 41) * 10 + 250))) / 2;
				freq3 = samples / (3580000.0 / (32 * ((random() % 41) * 10 + 325))) / 2;
			}

			sample1 = (i % freq1 < freq1 / 2) ? -127 : 127;
			sample2 = (i % freq2 < freq2 / 2) ? -127 : 127;
			sample3 = (i % freq3 < freq3 / 2) ? -127 : 127;

			wavedata[i] = (unsigned char)(((sample1+sample2+sample3)*0.1) + 127);
		}

		waveOutWrite(hwo, &hdr, sizeof(hdr));

		while (!(hdr.dwFlags & WHDR_DONE)) {
			Sleep(1);
		}
	}
}
DWORD WINAPI MoveDesk(LPVOID lpParameter){
	int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w, h);
	SelectObject(hcdc, hBitmap);
	for(int i = 0; i <= 100; i++){
		BitBlt(hcdc, 0, 0, w / 10, h, hdc, w / 10 * 9, 0, SRCCOPY);
		BitBlt(hcdc, w / 10, 0, w / 10 * 9, h, hdc, 0, 0, SRCCOPY);
		BitBlt(hdc, 0, 0, w, h, hcdc, 0, 0, SRCCOPY);
	}
	return 0;
}
DWORD WINAPI Click(LPVOID lpParameter){
	for(;;){
		mouse_event(MOUSEEVENTF_LEFTDOWN|MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		mouse_event(MOUSEEVENTF_RIGHTDOWN|MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
		Sleep(200);
		keybd_event(16,0,0,0);
		Sleep(200);
		keybd_event(16,0,KEYEVENTF_KEYUP,0);
		Sleep(200);
		keybd_event(random()%26+65,0,0,0);
	}
	return 0;
}
DWORD WINAPI gray(LPVOID lpParameter){
	int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, w / 2, h / 1);
	SelectObject(hcdc, hBitmap);
	for(;;){
		StretchBlt(hcdc, 0, 0, w / 2, h / 1, hdc, 0, 0, w, h, SRCCOPY);
		for(int i = 0; i < w / 2; i++){
			for(int j = 0; j < h / 1; j++){
				int r = GetRValue(GetPixel(hcdc, i, j));
				int g = GetGValue(GetPixel(hcdc, i, j));
				int b = GetBValue(GetPixel(hcdc, i, j));
				SetPixel(hcdc, i, j, RGB((r+g+b)/3, (r+g+b)/3, (r+g+b)/3));
			}
		}
		StretchBlt(hdc, 0, 0, w, h, hcdc, 0, 0, w / 2, h / 1, SRCCOPY);
		Sleep(250);
	}
	return 0;
}
DWORD WINAPI triangle(LPVOID lpParameter){
	int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	HDC hcdc = CreateCompatibleDC(hdc);
	HBITMAP hBitmap = CreateCompatibleBitmap(hdc, 50, 50);
	SelectObject(hcdc, hBitmap);
	//HDC hcdc2 = CreateCompatibleDC(hdc);
	//HBITMAP hBitmap2 = CreateCompatibleBitmap(hdc, w, h);
	//SelectObject(hcdc2, hBitmap2);
	for(int i = 0; i < 50; i++){
		for(int j = 0; j < 50; j++){
			SetPixel(hcdc,i,j,RGB(random()%256,random()%256,random()%256));
		}
	}
	HBRUSH hBrush = CreatePatternBrush(hBitmap);
	SelectObject(/*hcdc2*/hdc, hBrush);
	int numx = w / 150;
	if(w % 150 != 0){
		numx++;
	}
	int numy = h / 150;
	if(h % 150 != 0){
		numy++;
	}
	WAVEFORMATEX fmt = { WAVE_FORMAT_PCM, 1, 44100, 44100, 1, 8, 0 };

	HWAVEOUT hwo;
	waveOutOpen(&hwo, WAVE_MAPPER, &fmt, NULL, NULL, CALLBACK_NULL);
	
	const int bufsize = 44100 * 10;
	char *wavedata = (char *)LocalAlloc(0, bufsize);

	WAVEHDR hdr = { wavedata, bufsize, 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hwo, &hdr, sizeof(hdr));
	for(;;){
		for (int i = 0; i < bufsize; i++) {
			wavedata[i] = (unsigned char)((i % 257) / 2 + 100);
		}

		waveOutWrite(hwo, &hdr, sizeof(hdr));

		//BitBlt(hcdc2, 0, 0, w, h, hdc, 0, 0, SRCCOPY);

		for(int i = 0; i <= numx; i++){
			for(int j = 0; j <= numy; j++){
				POINT pt[] = {mkp(150 * i, 150 * j), mkp(150 * i + 150, 150 * j), mkp(150 * i, 150 * j + 150)};
				Polygon(/*hcdc2*/hdc, pt, 3);
			}
		}

		//BitBlt(hdc, 0, 0, w, h, hcdc2, 0, 0, SRCCOPY);
	}
	return 0;
}
LRESULT CALLBACK msgBoxHook(int nCode, WPARAM wParam, LPARAM lParam) {
	if (nCode == HCBT_CREATEWND) {
		CREATESTRUCT *pcs = ((CBT_CREATEWND *)lParam)->lpcs;
		int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
		if ((pcs->style & WS_DLGFRAME) || (pcs->style & WS_POPUP)) {
			HWND hwnd = (HWND)wParam;
			int x = random() % (w - pcs->cx);
			int y = random() % (h - pcs->cy);

			pcs->x = x;
			pcs->y = y;
		}
	}

	return CallNextHookEx(0, nCode, wParam, lParam);
}
DWORD WINAPI MessageThread(LPVOID parameter) {
	HHOOK hook = SetWindowsHookEx(WH_CBT, msgBoxHook, 0, GetCurrentThreadId());
	string Message;
	for(int i = 0; i < 20; i++){
		Message[i] = (char)(33 + random()%94);
	}
	MessageBox(NULL,Message.c_str(), Message.c_str(), MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
	UnhookWindowsHookEx(hook);

	return 0;
}
DWORD WINAPI MSGBX(LPVOID parameter) {
	for (;;) {
		CreateThread(NULL, 4096, &MessageThread, NULL, NULL, NULL);
		Sleep(2000);
	}
}
DWORD WINAPI Square(LPVOID parameter) {
	int w = GetSystemMetrics(SM_CXSCREEN),h = GetSystemMetrics(SM_CYSCREEN);
	HDC hdc = GetDC(NULL);
	for(;;){
		RECT rect;
		rect.bottom = random()%h + 1;
		rect.top = random()%rect.bottom;
		rect.right = random()%w + 1;
		rect.left = random()%rect.right;
		FillRect(hdc,&rect,CreateSolidBrush(RGB(rand() % 256, rand() % 256, rand() % 256)));
		Sleep(100);
	}
}
DWORD WINAPI _MSG(LPVOID parameter) {
	MessageBox(NULL,"", "TOO LATE", MB_OK | MB_SYSTEMMODAL | MB_ICONHAND);
	return 0;
}