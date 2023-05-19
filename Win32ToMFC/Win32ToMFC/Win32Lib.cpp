#include <windows.h>
#include <stdio.h>
#include <tchar.h>

LRESULT OnChar(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

LRESULT OnLButtonDown(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

LRESULT OnPaint(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

LRESULT OnDestroy(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

LRESULT CALLBACK WinProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

LRESULT OnCreate(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

typedef LRESULT(*FXN)(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
#define dim(x) (sizeof(x) / sizeof(x[0]))
struct tagMESSAGEMAP {
	UINT uMsg;
	FXN pFun;
};


tagMESSAGEMAP MessageMaps[] = {
	WM_CHAR,			OnChar,
	WM_LBUTTONDOWN,		OnLButtonDown,
	WM_PAINT,			OnPaint,
	WM_DESTROY,			OnDestroy,
	WM_CREATE,			OnCreate,
};

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd
)
{
	//1.
	WNDCLASS wndcls;
	wndcls.cbClsExtra = 0;
	wndcls.cbWndExtra = 0;
	wndcls.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndcls.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndcls.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndcls.hInstance = hInstance;
	wndcls.lpfnWndProc = WinProc;
	wndcls.lpszClassName = TEXT("win32ToMFC");
	wndcls.lpszMenuName = NULL;
	wndcls.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&wndcls);

	//2.
	HWND hWnd;
	hWnd = CreateWindow(
		wndcls.lpszClassName,
		TEXT("caption"),
		WS_OVERLAPPEDWINDOW,
		0,
		0,
		600,
		400,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	//3.
	ShowWindow(hWnd, SW_SHOWNORMAL);

	//4.
	UpdateWindow(hWnd);

	//5.
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WinProc(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	for (int i = 0; i < dim(MessageMaps); i++) {
		if (uMsg == MessageMaps[i].uMsg) {
			FXN fun = MessageMaps[i].pFun;
			return fun(hWnd, uMsg, wParam, lParam);
		}
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

LRESULT OnChar(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	TCHAR sztchar[20];
	wsprintf(sztchar, TEXT("you pressed %c key"), (TCHAR)wParam);
	MessageBox(hWnd, sztchar, TEXT("WM_CHAR"), 0);
	return 0;
}

LRESULT OnLButtonDown(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	HDC hdc;
	hdc = GetDC(hWnd);
	TextOut(hdc, 0, 50, TEXT("win32 to MFC"), wcslen(TEXT("win32 to MFC")));
	ReleaseDC(hWnd, hdc);
	return 0;
}

LRESULT OnPaint(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	HDC hDC;
	PAINTSTRUCT ps;
	hDC = BeginPaint(hWnd, &ps);
	TextOut(hDC, 0, 0, TEXT("Hello world!"), wcslen(TEXT("Hello world!")));
	EndPaint(hWnd, &ps);
	return 0;
}

LRESULT OnDestroy(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	PostQuitMessage(0);
	return 0;
}

LRESULT OnCreate(
	HWND hWnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
) {
	::MessageBox(NULL, __T("onCreate"), __T("onCreate") ,MB_OK);
	return 0;
}