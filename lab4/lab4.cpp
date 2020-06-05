#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <string>
#include <wchar.h>
#include <time.h>
#include <iostream>
#include <atltime.h>
using namespace std;

#pragma warning(disable:4996)
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName2[] = _T("MainFrame2");

int WINAPI _tWinMain(HINSTANCE This,		 // Дескриптор текущего приложения 
	HINSTANCE Prev, 	// В современных системах всегда 0 
	LPTSTR cmd, 		// Командная строка 
	int mode) 		// Режим отображения окна
{
	HWND hWnd;		// Дескриптор главного окна программы 
	MSG msg; 		// Структура для хранения сообщения 
	WNDCLASS wc; 	// Класс окна
	// Определение класса окна 
	wc.hInstance = This;
	wc.lpszClassName = WinName2; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 



	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName2,			// Имя класса окна 
		_T("Многопоточность"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		300,				// x 
		70, 				// y	 Размеры окна 
		600, 				// width 
		600, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 
	//SetWindowLong(, GWL_STYLE, WS_CHILD);
	ShowWindow(hWnd, mode); 				// Показать окно
	HMENU MainMenu = CreateMenu();
	HMENU hPopupMenu = CreatePopupMenu();
	HMENU hPopupMenu2 = CreatePopupMenu();
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu2, L"&Поток 1");
	{
		AppendMenu(hPopupMenu2, MF_STRING, 1003, L"Включить");
		AppendMenu(hPopupMenu2, MF_SEPARATOR, 0, L"");
		AppendMenu(hPopupMenu2, MF_STRING, 1004, L"Выключить");
	}
	AppendMenu(MainMenu, MF_STRING | MF_POPUP, (UINT)hPopupMenu, L"&Поток 2");
	{
		AppendMenu(hPopupMenu, MF_STRING, 1001, L"Включить");
		AppendMenu(hPopupMenu, MF_SEPARATOR, 0, L"");
		AppendMenu(hPopupMenu, MF_STRING, 1002, L"Выключить");
	}
	SetMenu(hWnd, MainMenu);

	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}
HANDLE hThread2;
HANDLE hThread1;
DWORD WINAPI Thread2(LPVOID t);
DWORD WINAPI Thread1(LPVOID t);

int a = 0;
BOOL bFin = true;
BOOL gfin = true;

// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);

	case WM_CREATE:
	{
		if (a == 0)
		{
			RECT rect = { 0,0,300,600 };
		}
		else
			if (a == 1)
			{
				RECT rect1 = { 300,0,600,600 };
			}
		InvalidateRect(hWnd, NULL, TRUE);
	}
	break;

	case WM_COMMAND:
		switch (wParam)
		{
		case 1001:
		{
			gfin = true;
			hThread2 = CreateThread(NULL, 0, Thread2, hWnd, 0, NULL);
			break;
		}
		case 1002:
		{
			TerminateThread(Thread2, 0);
			InvalidateRect(hWnd, NULL, TRUE);
			gfin = FALSE;
			break;
		}
		case 1003:
		{
			bFin = TRUE;
			hThread1 = CreateThread(NULL, 0, Thread1, hWnd, 0, NULL);
			break;
		}
		case 1004:
		{
			TerminateThread(Thread1, 0);
			InvalidateRect(hWnd, NULL, TRUE);
			bFin = FALSE;
			break;
		}
		}
	}
	return 0;
}

DWORD WINAPI Thread2(LPVOID t)
{
	RECT rect;
	PAINTSTRUCT ps;
	TCHAR buff[300];
	RECT recta = { 410,240,510,290 };
	while (gfin)
	{
		InvalidateRect((HWND)t, &recta, TRUE);
		UpdateWindow((HWND)t);
		_stprintf(buff, TEXT("%d"), GetCurrentTime());
		HDC hdc1 = GetDC(HWND(t));
		SetTextColor(hdc1, RGB(rand() % 255, rand() % 255, rand() % 255));
		TextOut(hdc1, 420, 250, buff, _tcslen(buff));
		EndPaint(HWND(t), &ps);
		Sleep(150);
	}
	a = 0;
	return 0;
}

DWORD WINAPI Thread1(LPVOID t)
{
	RECT rect;
	PAINTSTRUCT ps;
	while (bFin)
	{
		HDC hdc = GetDC(HWND(t));
		HBRUSH hBrush;
			RECT rect1 = { 0,0,300,600 };
			FillRect(hdc, &rect1, CreateSolidBrush(RGB(rand()%255, rand()%255, rand()%255)));
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			HBRUSH old = (HBRUSH)SelectObject(hdc, hBrush);
			Ellipse(hdc, 50, 150, 250, 350);
			DeleteObject(SelectObject(hdc, hBrush));
			Sleep(150);
		ReleaseDC(HWND(t), hdc);
	}
	a = 1;
	return (0);
}















/*	case WM_TIMER:
	{
		if (a == 0)
		{
			RECT rect = { 0,0,300,600 };
		}
		else
			if (a == 1)
			{
				RECT rect1 = { 300,0,600,600 };
			}
		InvalidateRect(hWnd, NULL, TRUE);
	}*/

	//	case WM_CREATE:
		//	SetTimer(hWnd, 1, 500, NULL);