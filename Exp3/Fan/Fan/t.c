#include<Windows.h>
#include<math.h>
#include<stdio.h>

//����ߴ���Ϣ
#define thisWidth			700//������
#define thisHeight			700//����߶�

#define PI					3.1415926

HWND hwnd;//������
POINT pt[3], cc = { 350,350 };//�������ꡢԲ������
INT R = 200;//���Ȱ뾶
INT theta = 0;//��ת�Ƕ�
HDC hDC, memDC;
HBITMAP hBMP;
HBRUSH hRGB[3], hNull;
PAINTSTRUCT ps;

//����ص�
LRESULT WINAPI CtlProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	INT i;

	switch (message)
	{
	case WM_CREATE:
		hDC = GetDC(hWnd);
		hRGB[0] = CreateSolidBrush(RGB(255, 0, 0));
		hRGB[1] = CreateSolidBrush(RGB(0, 255, 0));
		hRGB[2] = CreateSolidBrush(RGB(0, 0, 255));
		hNull = CreateHatchBrush(HS_CROSS, RGB(0, 125, 125));
		memDC = CreateCompatibleDC(hDC);
		hBMP = CreateCompatibleBitmap(hDC, thisWidth, thisHeight);
		SelectObject(memDC, hBMP);
		SetTimer(hWnd, 123456, 50, NULL);
		break;
	//�����ͼ
	case WM_PAINT:
		SelectObject(memDC, hNull);
		Ellipse(memDC, cc.x - R, cc.y - R, cc.x + R, cc.y + R);
		for (i = 0; i < 3; i++)
		{
			pt[i].x = (INT)(cc.x + R * cos(PI * (theta + i * 120) / 180));
			pt[i].y = (INT)(cc.y - R * sin(PI * (theta + i * 120) / 180));
			SelectObject(memDC, hRGB[i]);
			Pie(memDC, (INT)((cc.x + pt[i].x - R) / 2),
				(INT)((cc.y + pt[i].y - R) / 2),
				(INT)((cc.x + pt[i].x + R) / 2),
				(INT)((cc.y + pt[i].y + R) / 2),
				cc.x, cc.y, pt[i].x, pt[i].y);
		}
		theta -= 20;
		BitBlt(hDC, 0, 0, thisWidth, thisHeight, memDC, 0, 0, SRCCOPY);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, FALSE);
		break;
	//��������
	case WM_DESTROY:
		PostQuitMessage(0);
		KillTimer(hWnd, 123456);
		DeleteObject(hRGB[0]);
		DeleteObject(hRGB[1]);
		DeleteObject(hRGB[2]);
		DeleteObject(hNull);
		DeleteObject(hBMP);
		DeleteDC(memDC);
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, message, wParam, lParam);
}
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	MSG msg;
	WNDCLASSEX WC;//������
	INT ScreenWidth, ScreenHeight;//��Ļ��ȡ��߶�
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
	hwnd = CreateWindow(L"WND", L"����", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, (ScreenWidth - thisWidth) / 2, (ScreenHeight - thisHeight) / 2, thisWidth, thisHeight, NULL, 0, 0, 0);

	ShowWindow(hwnd, 1);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	ReleaseDC(hwnd, hDC);			//�ͷŻ�ͼDC

	return 0;
}