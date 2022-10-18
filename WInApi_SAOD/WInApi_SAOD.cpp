#define _CRT_SECURE_NO_WARNINGS
#include <Windows.h>
#include "Messages.h"

//#include "Test.h"
#include "Teory.h"

#include "WindowMSquare.h"
#include "WindowAES.h"
#include "WindowRSA.h"
#include "WindowElGamal.h"
#include "WindowTeory.h"
#include "WindowTest.h"



//Меню Главного окна
void MainWndAddMenu(HWND hwnd);

//Виджеты Главного окна
void MainWndAddWidgest(HWND hwnd);

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure);
LRESULT CALLBACK SoftwareMainProcedure(HWND hnwd, UINT msg, WPARAM wp, LPARAM lp);

int CALLBACK WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) 
{

	
	WNDCLASS SofrwareMainClass = NewWindowClass((HBRUSH)COLOR_WINDOW,LoadCursor(NULL, IDC_ARROW), hInst,LoadIcon(NULL,IDI_QUESTION),
		L"MainWindclass",SoftwareMainProcedure);

	if (!RegisterClassW(&SofrwareMainClass)) return -1;

	MSG SoftwareMainMessage = { 0 };

	CreateWindow(L"MainWindclass",L"Шифрование",WS_OVERLAPPEDWINDOW | WS_VISIBLE,600,300,600,500,NULL,NULL,NULL,NULL);

	
	/*ИНИЦИАЛИЗАЦИЯ ОКНА МАГИЧЕСКИЙ КВАДРАТ*/
	WNDCLASS SofrwareMainClassMSquare = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWindclassMSquare", SoftwareMainProcedureMSquare);

	if (!RegisterClassW(&SofrwareMainClassMSquare)) return -1;

	MSG SoftwareMainMessageMSquare = { 0 };
	/***************************************/

	/*ИНИЦИАЛИЗАЦИЯ ОКНА AES*/
	WNDCLASS SofrwareMainClassAES = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWindclassAES", SoftwareMainProcedureAES);

	if (!RegisterClassW(&SofrwareMainClassAES)) return -1;

	MSG SoftwareMainMessageAES = { 0 };
	/***************************************/

	/*ИНИЦИАЛИЗАЦИЯ ОКНА RSA*/
	WNDCLASS SofrwareMainClassRSA = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWindclassRSA", SoftwareMainProcedureRSA);

	if (!RegisterClassW(&SofrwareMainClassRSA)) return -1;

	MSG SoftwareMainMessageRSA = { 0 };
	/***************************************/

	/*ИНИЦИАЛИЗАЦИЯ ОКНА ElGamal*/
	WNDCLASS SofrwareMainClassElGamal = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWindclassElGamal", SoftwareMainProcedureElGamal);

	if (!RegisterClassW(&SofrwareMainClassElGamal)) return -1;

	MSG SoftwareMainMessageElGamal = { 0 };
	/***************************************/

	/*ИНИЦИАЛИЗАЦИЯ ОКНА ТЕОРИЯ*/
	WNDCLASS SofrwareMainClassT = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWindclassT", SoftwareMainProcedureT);

	if (!RegisterClassW(&SofrwareMainClassT)) return -1;

	MSG SoftwareMainMessageT = { 0 };
	/***************************************/

	/*ИНИЦИАЛИЗАЦИЯ ОКНА ТЕСТА*/
	WNDCLASS SofrwareMainClassTest = NewWindowClass((HBRUSH)COLOR_WINDOW, LoadCursor(NULL, IDC_ARROW), hInst, LoadIcon(NULL, IDI_QUESTION),
		L"MainWindclassTest", SoftwareMainProcedureTest);

	if (!RegisterClassW(&SofrwareMainClassTest)) return -1;

	MSG SoftwareMainMessageTest = { 0 };
	/***************************************/

	while (GetMessage(&SoftwareMainMessageMSquare, NULL, NULL, NULL))
	{

		TranslateMessage(&SoftwareMainMessage);
		DispatchMessage(&SoftwareMainMessage);

		TranslateMessage(&SoftwareMainMessageMSquare);
		DispatchMessage(&SoftwareMainMessageMSquare);

		TranslateMessage(&SoftwareMainMessageAES);
		DispatchMessage(&SoftwareMainMessageAES);

		TranslateMessage(&SoftwareMainMessageRSA);
		DispatchMessage(&SoftwareMainMessageRSA);

		TranslateMessage(&SoftwareMainMessageElGamal);
		DispatchMessage(&SoftwareMainMessageElGamal);

		TranslateMessage(&SoftwareMainMessageT);
		DispatchMessage(&SoftwareMainMessageT);

		TranslateMessage(&SoftwareMainMessageTest);
		DispatchMessage(&SoftwareMainMessageTest);
	}
	return 0;
}

WNDCLASS NewWindowClass(HBRUSH BGColor, HCURSOR Cursor, HINSTANCE hInst, HICON Icon, LPCWSTR Name, WNDPROC Procedure) 
{
	WNDCLASS NWC = { 0 };

	NWC.hIcon = Icon;
	NWC.hCursor = Cursor;
	NWC.hInstance = hInst;
	NWC.lpszClassName = Name;
	NWC.hbrBackground = BGColor;
	NWC.lpfnWndProc = Procedure;

	return NWC;
}

/*ГЛАВНОЕ ОКНО*/
LRESULT CALLBACK SoftwareMainProcedure(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) 
{
	switch (msg)
	{
		case WM_CREATE:

			MainWndAddMenu(hwnd);

			MainWndAddWidgest(hwnd);

			break;
		case WM_COMMAND:
			switch (wp)
			{
				case OnMenuClickMSquare:
					//MessageBox(hwnd, L"Что-то", L"Магический квадрат", MB_ICONINFORMATION);
					CreateWindow(L"MainWindclassMSquare", L"Магический квадрат", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 100, 600, 500, NULL, NULL, NULL, NULL);

				break;
				case OnMenuClickAES: 
				{
					CreateWindow(L"MainWindclassAES", L"AES", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 1100, 100, 600, 500, NULL, NULL, NULL, NULL);
					break;
				}
				case OnMenuClickRSA:
				{
					CreateWindow(L"MainWindclassRSA", L"RSA", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 100, 500, 600, 500, NULL, NULL, NULL, NULL);
					break;
				}
				case OnMenuClickElGamal:
				{
					CreateWindow(L"MainWindclassElGamal", L"ElGamal", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 1100, 500, 600, 500, NULL, NULL, NULL, NULL);
					break;
				}
				case OnMenuClickTEORY: 
				{
					InizializTeory();
					CreateWindow(L"MainWindclassT", L"Теория", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 900, 100, 900, 800, NULL, NULL, NULL, NULL);
					break;
				}
		
				case OnMenuClickTEST: 
				{
					
					CreateWindow(L"MainWindclassTest", L"Тест", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 450, 450, 900, 500, NULL, NULL, NULL, NULL);
					break;
				}
				case OnMenuEXIT:
					PostQuitMessage(EXIT_SUCCESS);

					break;
			}

			break;
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

		default: return DefWindowProc(hwnd, msg, wp, lp);
	}

}

void MainWndAddMenu(HWND hwnd)
{
	HMENU RootMenu = CreateMenu();// создать меню
	HMENU SUbMenu = CreateMenu();

	AppendMenu(SUbMenu, MF_STRING, OnMenuClickMSquare, L"Магический квадрат");
	AppendMenu(SUbMenu, MF_STRING, OnMenuClickAES, L"AES");
	AppendMenu(SUbMenu, MF_STRING, OnMenuClickRSA, L"RSA");
	AppendMenu(SUbMenu, MF_STRING, OnMenuClickElGamal, L"ElGamal");

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)SUbMenu, L"Алгоритмы");

	AppendMenu(RootMenu, MF_STRING, OnMenuEXIT, L"Выход");

	SetMenu(hwnd, RootMenu);// загрузить меню
}

void MainWndAddWidgest(HWND hwnd)
{

	CreateWindowA("static","Симметричное шифрование",WS_VISIBLE | WS_CHILD | ES_CENTER,0,75,600,20,hwnd,NULL,NULL,NULL); // Текст "Симметричное шифрование"

	CreateWindowA("button","Магический квадрат ",WS_VISIBLE | WS_CHILD,50,120,200,50,hwnd, reinterpret_cast<HMENU>(OnMenuClickMSquare),NULL,NULL); // кнопка "Магический квадрат"
	CreateWindowA("button", "AES ", WS_VISIBLE | WS_CHILD, 350, 120, 200, 50, hwnd, reinterpret_cast<HMENU>(OnMenuClickAES), NULL, NULL);// кнопка "AES"

	CreateWindowA("static", "Асимметричное шифрование", WS_VISIBLE | WS_CHILD | ES_CENTER, 0,200, 600, 20, hwnd, NULL, NULL, NULL); // Текст "Асимметричное шифрование"

	CreateWindowA("button", "RSA", WS_VISIBLE | WS_CHILD, 50, 220, 200, 50, hwnd, reinterpret_cast<HMENU>(OnMenuClickRSA), NULL, NULL); // кнопка "RSA"
	CreateWindowA("button", "ElGamal", WS_VISIBLE | WS_CHILD, 350, 220, 200, 50, hwnd, reinterpret_cast<HMENU>(OnMenuClickElGamal), NULL, NULL); // кнопка "ElGamal"

	CreateWindowA("button", "Пройти тест", WS_VISIBLE | WS_CHILD, 225, 300, 150, 20, hwnd, reinterpret_cast<HMENU>(OnMenuClickTEST), NULL, NULL); // кнопка "Пройти тест"
	CreateWindowA("button", "Теория", WS_VISIBLE | WS_CHILD, 450, 300, 100, 20, hwnd, reinterpret_cast<HMENU>(OnMenuClickTEORY), NULL, NULL);
	
}
/*КОНЕЦ ГЛАВНОГО ОКНА*******************************************************/