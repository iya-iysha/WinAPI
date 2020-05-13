#include <Windows.h>
#include <tchar.h>
#include <string.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

TCHAR WinName[] = _T("MainFrame");

int WINAPI _tWinMain (HINSTANCE This,		 // Дескриптор текущего приложения 
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
	wc.hbrBackground = (HBRUSH)(CreateSolidBrush(RGB(255, 255, 0))); 	// Заполнение окна белым цветом 


	// Регистрация класса окна
	if (!RegisterClass(&wc)) return 0;

	// Создание окна 
	hWnd = CreateWindow(WinName,			// Имя класса окна 
		_T("ИУ5-43 Ваксина Ия Лаб.1"), 		// Заголовок окна 
		WS_OVERLAPPEDWINDOW, 		// Стиль окна 
		CW_USEDEFAULT,				// x 
		CW_USEDEFAULT, 				// y	 Размеры окна 
		CW_USEDEFAULT, 				// width 
		CW_USEDEFAULT, 				// Height 
		HWND_DESKTOP, 				// Дескриптор родительского окна 
		NULL, 						// Нет меню 
		This, 						// Дескриптор приложения 
		NULL); 					// Дополнительной информации нет 

	ShowWindow(hWnd, mode); 				// Показать окно

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

INT f = 1;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc; // контекст устройства
	int x1 = 10;
	int y1 = 10;
	int x2 = 250;
	int y2 = 150;
	switch (message)		 // Обработчик сообщений
	{
	case WM_LBUTTONDOWN:
	{   
		hdc = GetDC(hWnd); // извлекает дескриптор дисплейного контекста устройства для рабочей области заданного окна
	//	RECT rectangle = { x1, y1, x2, y2 };
	//	RECT sq = { x1+250, y1, x2+150, y2 };
	//	FillRect(hdc, &rectangle, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
	//	FillRect(hdc, &sq, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		switch (f)
		{
			// заполнение первой строки геометрических фигур
		case 1:
		{   SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
		POINT rect[4] = { {x1,y1},{x2,y1},{x2,y2},{x1,y2} }; //прямоугольник
		Polygon(hdc, rect, 4);
		f++;
		break;
		}
		case 2:
		{
			SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
			POINT sq[4] = { {x1 + 250,y1},{x2 + 150,y1},{x2 + 150,y2},{x1 + 250,y2} }; // квадрат
			Polygon(hdc, sq, 4);
			f++;
			break;
		}
		case 3:
		{
			SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
			Ellipse(hdc, 410, 10, 550, 150); //окружность
			f++;
			break;
		}
		case 4:
		{
			SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
			POINT tre[3] = { {600,10},{560,150},{700,150} }; // треугольник
			Polygon(hdc, tre, 3);
			f++;
			break;
		}
		case 5:
		{
			SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
			POINT six[6] = { {710,80},{750,10},{830,10},{870,80},{830,150},{750,150} }; //шестиугольник
			Polygon(hdc, six, 6);
			f++;
			break;
		}

		// заполнение второй строки геометрических фигур
		case 6:
		{
			SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
			POINT para[4] = { {60,200},{250,200},{200,340},{10,340} }; //параллелограмм
			Polygon(hdc, para, 4);
			f++;
			break;
		}
		case 7:
		{
			SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
			Ellipse(hdc, 260, 200, 330, 340); //эллипс
			f++;
			break;
		}
		case 8:
		{
			SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
			POINT trap[4] = { {410,200},{570,200},{640,340},{340,340} }; //трапеция
			Polygon(hdc, trap, 4);
			f++;
			break;
		}
		case 9:
		{
			SelectObject(hdc, CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255)));
			POINT star[10] = { {700 - 50,250},{750 - 50,250},{773 - 50,200},{800 - 54,250},{850 - 55,250},{810 - 50,285},{830 - 50,340},{773 - 50,307},{716 - 50,340},{736 - 50,285} }; //звезда
			Polygon(hdc, star, 10);
			f++;
			break;
		}
		}
		ReleaseDC(hWnd, hdc); // освобождает контекст устройства окна
		break;
	}
	case WM_RBUTTONDOWN:
	{
		int xb, yb;
		hdc = GetDC(hWnd); // извлекает дескриптор дисплейного контекста устройства для рабочей области заданного окна
		xb = LOWORD(lParam);
		yb = HIWORD(lParam);
		LOGFONT lf;
		lf.lfHeight = 20;
		lf.lfItalic = 0; // курсив
		lf.lfStrikeOut = 0; // зачеркнуто
		lf.lfUnderline = 0; //подчеркнуто
		lf.lfWidth = 7;
		lf.lfWeight = 40;
		lf.lfCharSet = DEFAULT_CHARSET; //значение по умолчанию
		lf.lfPitchAndFamily = DEFAULT_PITCH; //ширина символов и семейство
		lf.lfEscapement = 0;
		SelectObject(hdc, CreateFontIndirect(&lf));
		if ((xb >= x1) && (xb <= x2) && (yb >= y1) && (yb <= y2))
		{
			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			TextOut(hdc, 75, 160, L"Прямоугольник", 13);
			break;
		} else
		if ((xb >= (x1 + 250)) && (xb <= (x2 + 150)) && (yb >= y1) && (yb <= y2))
		{
			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			TextOut(hdc, 300, 160, L"Квадрат", 7);
			break;
		} else
		if ((xb >= 430) && (xb <= 530) && (yb >= 20) && (yb <= 140))
		{
			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			TextOut(hdc, 465, 160, L"Круг", 4);
			break;
		} else
		if ((xb >= 570) && (xb <= 665) && (yb >= 30) && (yb <= 150))
		{
			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			TextOut(hdc, 585, 160, L"Треугольник", 11);
			break;
		} else
		if ((xb >= 715) && (xb <= 865) && (yb >= 10) && (yb <= 150))
		{
			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			TextOut(hdc, 738, 160, L"Шестиугольник", 13);
			break;
		} else
		if ((xb >= 30) && (xb <= 230) && (yb >= 200) && (yb <= 340))
		{
			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			TextOut(hdc, 60, 350, L"Параллелограмм", 14);
			break;
		} else
		if ((xb >= 260) && (xb <= 330) && (yb >= 200) && (yb <= 340))
		{
			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			TextOut(hdc, 277, 350, L"Овал", 4);
			break;
		} else
		if ((xb >= 370) && (xb <= 610) && (yb >= 200) && (yb <= 340))
		{
			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			TextOut(hdc, 460, 350, L"Трапеция", 8);
			break;
		} else
		if ((xb >= 650) && (xb <= 770) && (yb >= 220) && (yb <= 320))
		{
			SetTextColor(hdc, RGB(rand() % 255, rand() % 255, rand() % 255));
			TextOut(hdc, 700, 350, L"Звезда", 6);
			break;
		}
		else
		{
			TextOut(hdc, 0, 0, L"Звезда", 0);
			break;
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





/*	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);	
	break;*/
//PAINTSTRUCT ps; // экземпляр структуры графического вывода