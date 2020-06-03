#include <Windows.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND textbox;

TCHAR WinName[] = _T("MainFrame");
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
	wc.lpszClassName = WinName; 				// Имя класса окна 
	wc.lpfnWndProc = WndProc; 					// Функция окна 
	wc.style = CS_HREDRAW | CS_VREDRAW; 			// Стиль окна 
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION); 		// Стандартная иконка 
	wc.hCursor = LoadCursor(NULL, IDC_ARROW); 		// Стандартный курсор 
	wc.lpszMenuName = NULL; 					// Нет меню 
	wc.cbClsExtra = 0; 						// Нет дополнительных данных класса 
	wc.cbWndExtra = 0; 						// Нет дополнительных данных окна 
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 240, 240)));	// Заполнение окна белым цветом 

	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("Текстовый редактор"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		450,				// x 
		50, 				// y	 Размеры окна 
		500, 				// width 
		600, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 
	HMENU menu = CreateMenu();
	HMENU popmenu = CreatePopupMenu();
	AppendMenu(menu, MF_STRING | MF_POPUP, (UINT)popmenu, L"Файл");
	{
		AppendMenu(popmenu, MF_STRING, 1, L"Создать");
		AppendMenu(popmenu, MF_STRING, 2, L"Открыть");
		AppendMenu(popmenu, MF_STRING, 3, L"Сохранить");
	}
	AppendMenu(menu, MF_STRING, 4, L"Вырезать");
	AppendMenu(menu, MF_STRING, 5, L"Копировать");
	AppendMenu(menu, MF_STRING, 6, L"Вставить");
	AppendMenu(menu, MF_STRING, 7, L"Очистить");
	SetMenu(hWnd, menu);
	ShowWindow(hWnd, mode); 				// Показать окно
//	SetDlgItemText(hWnd, IDC_TEXTб);
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
string txt;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)		 // Обработчик сообщений
	{
	case WM_CREATE:
	{
		    textbox = CreateWindow(_T("EDIT"),
			_T(""),
			WS_BORDER | WS_VSCROLL | WS_CHILD | WS_VISIBLE | ES_AUTOVSCROLL | ES_MULTILINE,
			10, // x
			10, // y
			450,
			520,
			hWnd,
			(HMENU) 11,
			NULL,
			NULL
		);
		break;
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 1:
		{
			ofstream fout;
			fout.open("C:/Users/Ия/Desktop/taxt.txt");
			txt = "taxt";
			fout.close();
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		case 2:
		{
			ifstream fin;
			static char buf[1000];
			static wchar_t wbuf[1000];
			fin.open("C:/Users/Ия/Desktop/text.txt");
			txt = "text";
			if (!fin.is_open())
				MessageBox(hWnd, L"Указанный файл не найден!", L"Ошибка", MB_OK);
			else
			{
				for (int i = 0; i < 1000; i++)
				{
				        fin.seekg(0, ios::beg);
						fin.read(buf, i);
				}
			}
			fin.close();
			MultiByteToWideChar(CP_UTF8,
			0, buf, -1, wbuf, 1000);
			SendMessage(textbox, WM_SETTEXT, 1000, (LPARAM)wbuf);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		case 3:
		{
			ofstream fout;
			static char buf[1000];
			static wchar_t wbuf[1000];
			SendMessage(textbox, WM_GETTEXT, 1000, (LPARAM)wbuf);
			WideCharToMultiByte(CP_ACP,
				0, wbuf, -1, buf, 1000, nullptr, nullptr);
			if (txt == "text")
			    fout.open("C:/Users/Ия/Desktop/text.txt");
			else if (txt == "taxt")
				fout.open("C:/Users/Ия/Desktop/taxt.txt");
			for (int i = 0; i < 1000; i++)
			{
				fout.seekp(0, ios::beg);
				fout.write(buf, i);
			}
			fout.close();
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
		case 4:
			SendMessage(textbox, WM_CUT, 0, 0);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		case 5:
			SendMessage(textbox, WM_COPY, 0, 0);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		case 6:
			SendMessage(textbox, WM_PASTE, 0, 0);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		case 7:
			SendMessage(textbox, WM_CLEAR, 0, 0);
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		default: 			// Обработка сообщения по умолчанию 
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break; 			// Завершение программы 
	default: 			// Обработка сообщения по умолчанию 
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

