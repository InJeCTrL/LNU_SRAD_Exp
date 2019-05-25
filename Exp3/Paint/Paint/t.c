#include<Windows.h>
#include<math.h>
#include<stdio.h>

//窗体尺寸信息
#define thisWidth			700//程序宽度
#define thisHeight			700//程序高度


HWND hwnd;//主窗体
HDC hDC;
PAINTSTRUCT ps;
INT selDraw = 0;//1:椭圆 2:矩形
POINT dp1 = { 0,0 }, dp2 = { 0,0 };//左上右下

//窗体回调
LRESULT WINAPI CtlProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	INT i;

	switch (message)
	{
	case WM_KEYDOWN:
		switch (LOWORD(wParam))
		{
		case VK_CONTROL:
			selDraw = 1;
			dp1.x = 300;
			dp1.y = 300;
			dp2.x = 500;
			dp2.y = 600;
			break;
		case VK_SHIFT:
			selDraw = 2;
			dp1.x = 300;
			dp1.y = 300;
			dp2.x = 500;
			dp2.y = 700;
			break;
		case VK_RIGHT:
			dp2.x += 10;
			break;
		case VK_DOWN:
			dp2.y += 10;
			break;
		case VK_HOME:
			dp2.x -= 10;
			dp1.x -= 10;
			break;
		case VK_END:
			dp2.x += 10;
			dp1.x += 10;
			break;
		case VK_PRIOR:
			dp2.y -= 10;
			dp1.y -= 10;
			break;
		case VK_NEXT:
			dp2.y += 10;
			dp1.y += 10;
			break;
		default:
			break;
		}
		if (selDraw == 1)
		{
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			Ellipse(hDC, dp1.x, dp1.y, dp2.x, dp2.y);
		}
		else if (selDraw == 2)
		{
			InvalidateRect(hWnd, NULL, TRUE);
			UpdateWindow(hWnd);
			Rectangle(hDC, dp1.x, dp1.y, dp2.x, dp2.y);
		}
		break;
	//窗体销毁
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASSEX WC;//窗体类
	INT ScreenWidth, ScreenHeight;//屏幕宽度、高度
	INT i = 0;

	WC.cbSize = sizeof(WNDCLASSEX);
	WC.style = 0;
	WC.lpfnWndProc = CtlProc;
	WC.cbClsExtra = 0;
	WC.cbWndExtra = 0;
	WC.hInstance = hInstance;
	WC.hIcon = 0;
	WC.hCursor = 0;
	WC.hbrBackground = (HBRUSH)GetSysColorBrush(COLOR_BTNFACE);
	WC.lpszMenuName = 0;
	WC.lpszClassName = L"WND";
	WC.hIconSm = 0;

	ScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	RegisterClassEx(&WC);
	hwnd = CreateWindow(L"WND", L"Paint", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, (ScreenWidth - thisWidth) / 2, (ScreenHeight - thisHeight) / 2, thisWidth, thisHeight, NULL, 0, 0, 0);
	hDC = GetDC(hwnd);
	ShowWindow(hwnd, 1);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}