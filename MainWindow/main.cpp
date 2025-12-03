// MainWindow

#include<Windows.h>
#include<cstdio>
#include"resource.h"

#define IDC_BUTTON 1000 

CONST CHAR g_sz_WINDOW_CLASS[] = "My first window";

LRESULT CALLBACK WndProc(HWND hwnd, UINT UMsg, WPARAM wParam, LPARAM lParam);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPSTR lpCmdLine, INT nCmdShow)
{
	//	1) Регистрация класса окна.
	//	На этом этапе класс нашего окна регистрируется в ОС.
	//	Класс окна это не тип данных, как в ООП, класс любого окна представляет собой 
	//	самую обычную строку с именем класса.

	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(wClass));

	// Инициализируем размеры и стиль:

	wClass.style = NULL;
	wClass.cbSize = sizeof(wClass);
	wClass.cbClsExtra = 0;
	wClass.cbWndExtra = 0;

	// Инициализируем внешний вид окон:
	wClass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_BITCOIN));
	wClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON_PALM));
	//wClass.hIcon = (HICON)LoadImage(hInstance, "bitcoin.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);
	//wClass.hIconSm = (HICON)LoadImage(hInstance, "palm.ico", IMAGE_ICON, LR_DEFAULTSIZE, LR_DEFAULTSIZE, LR_LOADFROMFILE);

	wClass.hCursor = (HCURSOR)LoadImage
	(
		hInstance,
		"starcraft-original\\Working In Background.ani",
		IMAGE_CURSOR,
		LR_DEFAULTSIZE, LR_DEFAULTSIZE,
		LR_LOADFROMFILE
	);

	//wClass.hCursor = LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1));
	wClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

	// Инициализация системных переменных:

	wClass.hInstance = hInstance;
	wClass.lpszClassName = g_sz_WINDOW_CLASS;
	wClass.lpszMenuName = NULL;
	wClass.lpfnWndProc = WndProc;

	if (RegisterClassEx(&wClass) == NULL)
	{
		MessageBox(NULL, "Class registration failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}

	//	2) Создание окна:

	INT screen_width = GetSystemMetrics(SM_CXSCREEN);
	INT screen_height = GetSystemMetrics(SM_CYSCREEN);
	INT window_width = screen_width * 3 / 4;
	INT window_height = screen_height * 3 / 4;
	INT x_position = screen_width / 8;
	INT y_position = screen_height / 8;

	HWND hwnd = CreateWindowEx
	(
		NULL,	//exStyle
		g_sz_WINDOW_CLASS,	//Имя класса окна
		g_sz_WINDOW_CLASS,	//Заголовок окна
		WS_OVERLAPPEDWINDOW,	//Стиль окна. Стили всегда зависят от класса окна.
		//'WS_OVERLAPPEDWINDOW' - нлавное окно
		//CW_USEDEFAULT, CW_USEDEFAULT,	//Position
		x_position,	y_position,//Position
		//640, 480,	//Размер окна
		window_width, window_height,	//Размер окна
		NULL,
		NULL,	//Для главного окна это ResourceID главного меню, 
		//для дочернего окна (Control) - ResourceID дочернего окна (IDC_BUTTON_COPY)
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		MessageBox(NULL, "Windows creation failed", NULL, MB_OK | MB_ICONERROR);
		return 0;
	}
	ShowWindow(hwnd, nCmdShow); // Задает режим отражения окна - Развернуто на весь экран,
	//Свернуто в окно, Свернуто на панель задач
	UpdateWindow(hwnd); // Обновляет рабочую область указанного окна, 
	// отправляя сообщение в 'WM_PAINT',
	// если клиентская область окна не пустая.

//	3) Запуск цикла сообщений:

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&msg); // Преобразует сообщения виртуальных клавиш 
		// в символьные сообщения
		DispatchMessage(&msg);  // Отправляет сообщение в процедуру окна
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
	{	
		HWND hButton = CreateWindowEx
		(
			NULL,		//exStyle
			"Button",	//Class
			"Кнопка",	//Title
			WS_CHILD | WS_VISIBLE,	//Style
			10, 10,		//Position
			150, 80,	//Size
			hwnd,		//Parent
			(HMENU)1000,	// Для главного окна - это ResourceID главного меню,
							// Для дочернего окна (элемента управления окна) - 
							// это ResourceID дочернего элемента
			GetModuleHandle(NULL),	// hInstance
			NULL		// ???????
		);
	}
		break;

	case WM_MOVE:
	case WM_SIZE:
	{
		RECT window_rect = {};
		GetWindowRect(hwnd, &window_rect);
		CONST INT SIZE = 256;
		CHAR sz_title[SIZE]{};

		wsprintf
		(
			sz_title,
			"%s, Position: %ix%i;\tSize: %ix%i",
			g_sz_WINDOW_CLASS,
			window_rect.left, window_rect.top,
			window_rect.right - window_rect.left,
			window_rect.bottom - window_rect.top
		);
		SendMessage(hwnd, WM_SETTEXT, 0, (LPARAM)sz_title);
	}
	break;

	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON:
			MessageBox(hwnd, "Cursor check", "Info", MB_OK | MB_ICONINFORMATION);
			break;
		}
	}	
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
	return FALSE;

}

