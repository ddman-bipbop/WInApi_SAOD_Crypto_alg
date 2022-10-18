#include "WindowAES.h"
#include "AES.h"

char BufferAES[TextBufferSize];

//сохранение в файл текста
void SaveDataAES(LPCSTR path, HWND hControlField);
//чтение из файла текста
void LoadDataAES(LPCSTR path, HWND hControlField);
//Очищает буффер
void ClearBufferAES(char* buffer);

HWND hReadControlAES;
HWND hWriteControlAES;
//HWND hStaticFiled;
HWND hKeyAES;

LRESULT CALLBACK SoftwareMainProcedureAES(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:

		MainWndAddWidgestAES(hwnd);

		break;
	case WM_COMMAND:
		switch (wp)
		{
		case 1:
			//MessageBox(hwnd, L"Что-то", L"Магический квадрат", MB_ICONINFORMATION);

			break;
		case OnAESCrypt:
		{
			ClearBufferAES(BufferAES);
			SetWindowTextA(hWriteControlAES, "");
			GetWindowTextA(hReadControlAES, BufferAES, TextBufferSize); // считывает текст из поля ВВОД
			SaveDataAES("AES/tempInCryptoText.txt", hReadControlAES); //сохранение текста из поля ВВОД в файл
			EncodeAES();
			LoadDataAES("AES/CryptoText.txt", hWriteControlAES);
			break;
		}
		case OnAESDecode:
		{
			ClearBufferAES(BufferAES);
			SetWindowTextA(hWriteControlAES, "");
			SaveDataAES("AES/CryptoText.txt", hWriteControlAES);
			GetWindowTextA(hReadControlAES, BufferAES, TextBufferSize); // считывает текст из поля ВВОД
			SaveDataAES("AES/tempInCryptoText.txt", hReadControlAES); //сохранение текста из поля ВВОД в файл
			DecodeAES();
			ClearBufferAES(BufferAES);
			LoadDataAES("AES/CryptoText.txt", hWriteControlAES);
			break;
		}

		case OnMenuEXIT:
		{
			PostQuitMessage(EXIT_SUCCESS);

			break;
		}
		case OnAESLoadFromFile:
		{
			ClearBufferAES(BufferAES);
			SetWindowTextA(hReadControlAES, "");
			LoadDataAES("AES/input.txt", hReadControlAES);
			break;
		}
		case OnAESWriteToFile:
		{
			SaveDataAES("AES/output.txt", hWriteControlAES);
			break;
		}
		case OnAESGeneredKey:
		{
			GeneratedPass();
			LoadDataAES("AES/inputKey.txt", hKeyAES);
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

void MainWndAddWidgestAES(HWND hwnd)
{

	CreateWindowA("static", "ВВОД", WS_VISIBLE | WS_CHILD, 100, 15, 100, 20, hwnd, NULL, NULL, NULL);
	CreateWindowA("static", "ВЫВОД", WS_VISIBLE | WS_CHILD, 400, 15, 100, 20, hwnd, NULL, NULL, NULL);

	hReadControlAES = CreateWindowA("edit", "Text", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL, 15, 55, 250, 80, hwnd, NULL, NULL, NULL);
	hWriteControlAES = CreateWindowA("edit", "Text", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL, 300, 55, 250, 80, hwnd, NULL, NULL, NULL);

	CreateWindowA("button", "Зашифровать", WS_VISIBLE | WS_CHILD, 15, 150, 250, 20, hwnd, reinterpret_cast<HMENU>(OnAESCrypt), NULL, NULL);
	CreateWindowA("button", "Расшифровать", WS_VISIBLE | WS_CHILD, 300, 150, 250, 20, hwnd, reinterpret_cast<HMENU>(OnAESDecode), NULL, NULL);

	CreateWindowA("button", "ВВОД из файла", WS_VISIBLE | WS_CHILD, 15, 180, 250, 20, hwnd, reinterpret_cast<HMENU>(OnAESLoadFromFile), NULL, NULL);
	CreateWindowA("button", "ВЫВОД в файл", WS_VISIBLE | WS_CHILD, 300, 180, 250, 20, hwnd, reinterpret_cast<HMENU>(OnAESWriteToFile), NULL, NULL);

	CreateWindowA("static", "КЛЮЧ", WS_VISIBLE | WS_CHILD, 250, 210, 100, 20, hwnd, NULL, NULL, NULL);
	hKeyAES =  CreateWindowA("edit", " ", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL, 75, 235, 450, 180, hwnd, NULL, NULL, NULL);
	LoadDataAES("AES/inputKey.txt", hKeyAES);

	CreateWindowA("button", "Сгенерировать СЛУЧАЙНЫЙ ключ", WS_VISIBLE | WS_CHILD, 150, 425, 250, 20, hwnd, reinterpret_cast<HMENU>(OnAESGeneredKey), NULL, NULL);

}

void SaveDataAES(LPCSTR path, HWND hControlField)
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

void LoadDataAES(LPCSTR path, HWND hControlField)
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
	ReadFile(FileToLoad, BufferAES, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(hControlField, BufferAES);

	CloseHandle(FileToLoad);
}

void ClearBufferAES(char* buffer)
{
	for (size_t i = 0; i < TextBufferSize; i++)
		buffer[i] = '\0';
}