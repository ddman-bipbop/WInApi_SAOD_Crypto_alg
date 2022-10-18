#include "WindowMSquare.h"
#include "MagicSquare.h"

char BufferMS[TextBufferSize];
HWND hReadControlMSquare;
HWND hWriteControlMsquare;
HWND hStaticFiled;
HWND hKeyMSquare;

//сохранение в файл текста
void SaveDataMS(LPCSTR path,HWND hControlField);
//чтение из файла текста
void LoadDataMS(LPCSTR path, HWND hControlField);
//Очищает буффер
void ClearBufferMS(char* buffer);

/*МАГИЧЕСКИЙ КВАДРАТ*/
LRESULT CALLBACK SoftwareMainProcedureMSquare(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:

		MainWndAddWidgestMSquare(hwnd);
		
		break;
	case WM_COMMAND:
		switch (wp)
		{
		case 1:
			//MessageBox(hwnd, L"Что-то", L"Магический квадрат", MB_ICONINFORMATION);

			break;
		case OnMSquareCrypt:
		{
			ClearBufferMS(BufferMS);
			SetWindowTextA(hWriteControlMsquare, "");
			int readChar = GetWindowTextA(hReadControlMSquare, BufferMS, TextBufferSize); // считывает текст из поля ВВОД
			SaveDataMS("MagicSquare/tempInCryptoText.txt", hReadControlMSquare); //сохранение текста из поля ВВОД в файл
			MainMSquareCrypto(1);//сохраняет результат в файл CryptoText.txt
			LoadDataMS("MagicSquare/CryptoText.txt", hWriteControlMsquare);
			
			break;
		}
		case OnMSquareDecrypto: 
		{
			ClearBufferMS(BufferMS);
			SetWindowTextA(hWriteControlMsquare, "");
			GetWindowTextA(hReadControlMSquare, BufferMS, TextBufferSize); // считывает текст из поля ВВОД
			SaveDataMS("MagicSquare/tempInCryptoText.txt", hReadControlMSquare); //сохранение текста из поля ВВОД в файл
			MainMSquareCrypto(2);//сохраняет результат в файл CryptoText.txt
			LoadDataMS("MagicSquare/CryptoText.txt", hWriteControlMsquare);

			break;
		}
		case OnMSquareLoadFromFile:
		{
			ClearBufferMS(BufferMS);
			SetWindowTextA(hReadControlMSquare, "");
			LoadDataMS("MagicSquare/input.txt", hReadControlMSquare);// Запись текста в поле ВВОД из файла

			break;
		}

		case OnMenuEXIT: 
		{
			PostQuitMessage(EXIT_SUCCESS);

			break;
		}
		case OnMSquareWriteToFile: 
		{
			SaveDataMS("MagicSquare/output.txt", hWriteControlMsquare);
			break;
		}
		case OnMSquareGeneredKey:
		{
			MainMSquareCrypto(4);
			//MainMSquareCrypto(3);//вывести матрицу\ключ в файл
			LoadDataMS("MagicSquare/keyMSquare.txt", hKeyMSquare);
			break;
		}
			

		}
	
	


		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hwnd, msg, wp, lp);
	}

}

void MainWndAddWidgestMSquare(HWND hwnd)
{

	hStaticFiled = CreateWindowA("static", "ВВОД", WS_VISIBLE | WS_CHILD, 100, 15, 100, 20, hwnd, NULL, NULL, NULL);
	CreateWindowA("static", "ВЫВОД", WS_VISIBLE | WS_CHILD, 400, 15, 100, 20, hwnd, NULL, NULL, NULL);

	hReadControlMSquare = CreateWindowA("edit", "Text", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL, 15, 55, 250, 80, hwnd, NULL, NULL, NULL);
	hWriteControlMsquare = CreateWindowA("edit", "Text", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL, 300, 55, 250, 80, hwnd, NULL, NULL, NULL);

	CreateWindowA("button", "Зашифровать", WS_VISIBLE | WS_CHILD, 15, 150, 250, 20, hwnd, reinterpret_cast<HMENU>(OnMSquareCrypt), NULL, NULL);
	CreateWindowA("button", "Расшифровать", WS_VISIBLE | WS_CHILD, 300, 150, 250, 20, hwnd, reinterpret_cast<HMENU>(OnMSquareDecrypto), NULL, NULL);

	CreateWindowA("button", "ВВОД из файла", WS_VISIBLE | WS_CHILD, 15, 180, 250, 20, hwnd, reinterpret_cast<HMENU>(OnMSquareLoadFromFile), NULL, NULL);
	CreateWindowA("button", "ВЫВОД в файл", WS_VISIBLE | WS_CHILD, 300, 180, 250, 20, hwnd, reinterpret_cast<HMENU>(OnMSquareWriteToFile), NULL, NULL);

	CreateWindowA("static", "КЛЮЧ", WS_VISIBLE | WS_CHILD, 250, 210, 100, 20, hwnd, NULL, NULL, NULL);
	hKeyMSquare = CreateWindowA("edit", " ", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL, 75, 235, 450, 180, hwnd, NULL, NULL, NULL);
	MainMSquareCrypto(3);//вывести матрицу\ключ в файл
	LoadDataMS("MagicSquare/keyMSquare.txt", hKeyMSquare);

	CreateWindowA("button", "Сгенерировать ключ из файла", WS_VISIBLE | WS_CHILD, 150, 425, 250, 20, hwnd, reinterpret_cast<HMENU>(OnMSquareGeneredKey), NULL, NULL);

}
/*КОНЕЦ МАГИЧЕСКОГО КВАДРАТА******************************/

void SaveDataMS(LPCSTR path, HWND hControlField)
{
	HANDLE FileToSave = CreateFileA(
		path,
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL);
	int saveLenght = GetWindowTextLength(hControlField) + 1;
	char* data = new char[saveLenght];

	saveLenght = GetWindowTextA(hControlField, data, saveLenght);
	DWORD bytesIterated;
	WriteFile(FileToSave, data, saveLenght, &bytesIterated, NULL);

	CloseHandle(FileToSave);
	delete[]data;
}

void LoadDataMS(LPCSTR path, HWND hControlField) 
{
	HANDLE FileToLoad = CreateFileA(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD bytesIterated;
	ReadFile(FileToLoad,BufferMS,TextBufferSize,&bytesIterated,NULL);

	SetWindowTextA(hControlField, BufferMS);

	CloseHandle(FileToLoad);
}

void ClearBufferMS(char* buffer)
{
	for (size_t i = 0; i < TextBufferSize; i++)
		buffer[i] = '\0';
}