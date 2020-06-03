#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include "dz.h"
#include "math.h"
#include <string>
#include <wchar.h>
#include<ctime>

BOOL DLine(HDC hdc, double x1, double y1, double x2, double y2);
#define MAX_LOADSTRING 100
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;
HDC hdc;
int  xView, yView, test = -10, ff = 0, check = 0;;
double i, r;
double y, x;
char Buf[100];
#define pi 3.14

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
	wc.hCursor = LoadCursor(hInst, MAKEINTRESOURCE(230)); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); 	// Заполнение окна белым цветом 

	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName2,			// Имя класса окна 
		_T("Построение графика"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		100, 110,//положение окна на экране по x и по y
		500, 500,//размеры по x и y
		nullptr, nullptr, hInst, nullptr);
	//SetWindowLong(, GWL_STYLE, WS_CHILD);
	ShowWindow(hWnd, mode); 				// Показать окно
	HMENU MainMenu = CreateMenu();
		AppendMenu(MainMenu, MF_STRING, 1001, "[-5;5]");
		AppendMenu(MainMenu, MF_SEPARATOR, 0, "");
		AppendMenu(MainMenu, MF_STRING, 1002, "[-10;10]");
		AppendMenu(MainMenu, MF_SEPARATOR, 0, "");
		AppendMenu(MainMenu, MF_STRING, 1003, "Синий");
		AppendMenu(MainMenu, MF_SEPARATOR, 0, "");
		AppendMenu(MainMenu, MF_STRING, 1004, "Зеленый");
	SetMenu(hWnd, MainMenu);
	UpdateWindow(hWnd);
	// Цикл обработки сообщений 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); 		// Функция трансляции кодов нажатой клавиши 
		DispatchMessage(&msg); 		// Посылает сообщение функции WndProc() 
	}
	return 0;
}


// Оконная функция вызывается операционной системой
// и получает сообщения из очереди для данного приложения
int aaa = 0;
int aaaa = 0;
HPEN hPen;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;//создаём контекст устройства
	PAINTSTRUCT ps;
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Разобрать выбор в меню:
		switch (wmId)
		{
		case 1001:
			aaa = 1;
			test = -5;
			SendMessage(hWnd, WM_PAINT, WPARAM(hWnd), NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 1002:
			aaa = 0;
			test = -10;
			SendMessage(hWnd, WM_PAINT, WPARAM(hWnd), NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 1003:
			aaaa = 1;
			SendMessage(hWnd, WM_PAINT, WPARAM(hWnd), NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case 1004:
			aaaa = 0;
			SendMessage(hWnd, WM_PAINT, WPARAM(hWnd), NULL);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}
	case WM_SIZE:
		xView = LOWORD(lParam);
		yView = HIWORD(lParam);

		break;


		//сообщение рисования

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SetMapMode(hdc, MM_ISOTROPIC); //логические единицы отображаем, как физические
		SetWindowExtEx(hdc, 900, 900, NULL); //Длина осей
		SetViewportExtEx(hdc, xView, -yView, NULL); //Определяем область вывода
		SetViewportOrgEx(hdc, xView / 2, yView / 2, NULL); //Начало координат

		//Рисуем оси координат
		DLine(hdc, 0, -450, 0, 450);//ось У
		DLine(hdc, -450, 0, 450, 0);//ось Х
		if (ff == 0) {
			MoveToEx(hdc, 0, 0, NULL);
		}//перемещаемся в начало координат

		//Создание красного пера
		if (aaa == 0)
		{
			for (i = -450; i <= 450; i++) {
				x = i / 45;
				if (aaaa == 0)
				{
					hPen = CreatePen(1, 2, RGB(0, 255, 0));
				}
				else
				{
					if (aaaa == 1)
					{
						hPen = CreatePen(1, 2, RGB(0, 0, 255));
					}
				}
				//srand(time(0));
				SelectObject(hdc, hPen);
				y = (log10(-abs(log10(abs(abs(abs(sin(abs(x)) - 2) - 4) - 3))) + 4));
				y *= 45;
				x *= 45;
				if ((ff == 0)) {
					MoveToEx(hdc, x, y, NULL);
					ff = 1;
				}
				LineTo(hdc, x, y);
				DeleteObject(hPen);
			}
		}
		else
		{
			if (aaa == 1)
			{
				for (i = -450; i <= 450; i++) {
					x = i / 90;
					if (aaaa == 0)
					{
						hPen = CreatePen(1, 2, RGB(0, 255, 0));
					}
					else
					{
						if (aaaa == 1)
						{
							hPen = CreatePen(1, 2, RGB(0, 0, 255));
						}
					}
					//srand(time(0));
					SelectObject(hdc, hPen);
					y = (log10(-abs(log10(abs(abs(abs(sin(abs(x)) - 2) - 4) - 3))) + 4));
					y *= 90;
					x *= 90;
					if ((ff == 0)) {
						MoveToEx(hdc, x, y, NULL);
						ff = 1;
					}
					LineTo(hdc, x, y);
					DeleteObject(hPen);
				}
			}
		}
		hPen = CreatePen(1, 1, RGB(255, 0, 0));
		SelectObject(hdc, hPen);

		if (check == 0) {
			if (aaa == 0)
			{
				for (i = -450; i <= 450; i += 45)
				{
					DLine(hdc, i, 3, i, -3);
					DLine(hdc, -3, i, 3, i);

					//int test = i;

					sprintf_s(Buf, "%d", test);
					SetBkMode(hdc, TRANSPARENT);
					if (test == 0) {
						TextOut(hdc, 0, i, Buf, strlen(Buf));
					}
					else {
						TextOut(hdc, i - 5, -5, Buf, strlen(Buf));
						TextOut(hdc, 3, i + 9, Buf, strlen(Buf));
					}

					test++;
				}
				check = 1;
			}
			else
			{
				if (aaa == 1)
				{
					for (i = -450; i <= 450; i += 90)
					{
						DLine(hdc, i, 3, i, -3);
						DLine(hdc, -3, i, 3, i);
						sprintf_s(Buf, "%d", test);
						SetBkMode(hdc, TRANSPARENT);
						if (test == 0) {
							TextOut(hdc, 0, i, Buf, strlen(Buf));
						}
						else {
							TextOut(hdc, i - 5, -5, Buf, strlen(Buf));
							TextOut(hdc, 3, i + 9, Buf, strlen(Buf));
						}

						test++;
					}
					check = 1;
				}
			}
		}
		//InvalidateRect(hWnd, NULL, TRUE);
		//ValidateRect(hWnd, NULL); //Обновляем экран
		EndPaint(hWnd, &ps);
		ff = 0;
		check = 0;
		if (aaa == 0)
		{
			test = -10;
		}
		else
		{
			if (aaa == 1)
			{
				test = -5;
			}
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);


	}
	return 0;
}
BOOL DLine(HDC hdc, double x1, double y1, double x2, double y2)
{
	MoveToEx(hdc, x1, y1, NULL); //сделать текущими координаты x1, y1
	return LineTo(hdc, x2, y2); //нарисовать линию
}
// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}