#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WinProc(
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
);

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
	HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	switch (uMsg)
	{
	case WM_CHAR:
		TCHAR sztchar[20];
		wsprintf(sztchar, TEXT("you pressed %c key"), (TCHAR)wParam);
		MessageBox(hwnd, sztchar, TEXT("WM_CHAR"), 0);
		break;
	case WM_LBUTTONDOWN:
		HDC hdc;
		hdc = GetDC(hwnd);
		TextOut(hdc, 0, 50, TEXT("win32 to MFC"), wcslen(TEXT("win32 to MFC")));
		ReleaseDC(hwnd, hdc);
		break;
	case WM_PAINT:
		HDC hDC;
		PAINTSTRUCT ps;
		hDC = BeginPaint(hwnd, &ps);
		TextOut(hDC, 0, 0, TEXT("Hello world!"), wcslen(TEXT("Hello world!")));
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}

	return 0;
}