#include<Windows.h>
#include<math.h>
#include<stdio.h>

//����ߴ���Ϣ
#define thisWidth			700//������
#define thisHeight			700//����߶�

#define PI					3.1415926

HWND hwnd;//������
POINT pt[10], cc = { 350,350 };//�������ꡢԲ������
INT R = 200;//���ְ뾶
INT theta = 0;//��ת�Ƕ�
HDC hDC;
PAINTSTRUCT ps;
TCHAR poem[] = L"����ǧ��Ŀ����һ��¥";
HANDLE hFont;

//����ص�
LRESULT WINAPI CtlProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	INT i;

	switch (message)
	{
	case WM_CREATE:
		hFont = CreateFont(20,20,0,0,FW_NORMAL,FALSE,FALSE,0,ANSI_CHARSET, OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS,L"����");
		SetTimer(hWnd, 123456, 100, NULL);
		break;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE);
		break;
	//�����ͼ
	case WM_PAINT:
		hDC = BeginPaint(hWnd, &ps);
		SetBkMode(hDC, TRANSPARENT);
		SelectObject(hDC, hFont);
		for (i = 0; i < 10; i++)
		{
			pt[i].x = (INT)(cc.x + R * cos(PI * (theta - i * 36) / 180));
			pt[i].y = (INT)(cc.y - R * sin(PI * (theta - i * 36) / 180));
			TextOut(hDC, pt[i].x, pt[i].y, poem + i, 1);
			SetTextColor(hDC, RGB(220 - i * 15, 0, 0));
		}
		theta += 5;
		EndPaint(hWnd, &ps);
		break;
	//��������
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
	hwnd = CreateWindow(L"WND", L"����ǧ��Ŀ����һ��¥", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX, (ScreenWidth - thisWidth) / 2, (ScreenHeight - thisHeight) / 2, thisWidth, thisHeight, NULL, 0, 0, 0);

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