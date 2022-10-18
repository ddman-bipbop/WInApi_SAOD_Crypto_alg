#include "WindowRSA.h"
#include "RSA.h"

char BufferRSA[TextBufferSize];

//сохранение в файл текста
void SaveDataRSA(LPCSTR path, HWND hControlField);
//чтение из файла текста
void LoadDataRSA(LPCSTR path, HWND hControlField);
//Очищает буффер
void ClearBufferRSA(char* buffer);

HWND hReadFieldRSA;
HWND hWriteFieldRSA;
HWND hNKeyRSA;
HWND hOpenKeyRSA;
HWND hCloseKeyRSA;

/*МАГИЧЕСКИЙ КВАДРАТ*/
LRESULT CALLBACK SoftwareMainProcedureRSA(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		MainWndAddWidgestRSA(hwnd);

		break;
	case WM_COMMAND:
		switch (wp)
		{
		case 1:
			//MessageBox(hwnd, L"Что-то", L"Магический квадрат", MB_ICONINFORMATION);

			break;
		case OnRSAEncode:
		{
			ClearBufferRSA(BufferRSA);
			SetWindowTextA(hWriteFieldRSA, "");
			GetWindowTextA(hReadFieldRSA, BufferRSA, TextBufferSize); // считывает текст из поля ВВОД
			SaveDataRSA("RSA/tempInCryptoText.txt", hReadFieldRSA); //сохранение текста из поля ВВОД в файл
			RSA_Encrypt();
			ClearBufferRSA(BufferRSA);
			LoadDataRSA("RSA/CryptoText.txt", hWriteFieldRSA);
			break;
		}
		case OnRSADecode:
		{
			ClearBufferRSA(BufferRSA);
			SetWindowTextA(hWriteFieldRSA, "");
			GetWindowTextA(hReadFieldRSA, BufferRSA, TextBufferSize); // считывает текст из поля ВВОД
			SaveDataRSA("RSA/tempInCryptoText.txt", hReadFieldRSA); //сохранение текста из поля ВВОД в файл
			RSA_Decrypt();
			ClearBufferRSA(BufferRSA);
			LoadDataRSA("RSA/CryptoText.txt", hWriteFieldRSA);
			break;
		}
		case OnRSALoadFromFile:
		{
			ClearBufferRSA(BufferRSA);
			SetWindowTextA(hReadFieldRSA, "");
			LoadDataRSA("RSA/input.txt", hReadFieldRSA);
			break;
		}
		case OnRSAWriteToFile: 
		{
			SaveDataRSA("RSA/output.txt", hWriteFieldRSA);
			break;
		}
		case OnRSAGeneredKey:
		{
			SetWindowTextA(hNKeyRSA, "");
			SetWindowTextA(hOpenKeyRSA, "");
			SetWindowTextA(hCloseKeyRSA, "");
			RSA_Initialize();
			ClearBufferRSA(BufferRSA);
			LoadDataRSA("RSA/n.txt", hNKeyRSA);
			ClearBufferRSA(BufferRSA);
			LoadDataRSA("RSA/e.txt", hOpenKeyRSA);
			ClearBufferRSA(BufferRSA);
			LoadDataRSA("RSA/d.txt", hCloseKeyRSA);
			ClearBufferRSA(BufferRSA);
			break;
		}
		case OnMenuEXIT:
		{
			PostQuitMessage(EXIT_SUCCESS);

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

void MainWndAddWidgestRSA(HWND hwnd)
{
	CreateWindowA("static", "ВВОД", WS_VISIBLE | WS_CHILD, 100, 15, 100, 20, hwnd, NULL, NULL, NULL);
	CreateWindowA("static", "(Только числа)", WS_VISIBLE | WS_CHILD, 75, 37, 100, 20, hwnd, NULL, NULL, NULL);
	CreateWindowA("static", "ВЫВОД", WS_VISIBLE | WS_CHILD, 400, 15, 100, 20, hwnd, NULL, NULL, NULL);

	hReadFieldRSA = CreateWindowA("edit", "111", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL, 15, 55, 250, 80, hwnd, NULL, NULL, NULL);
	hWriteFieldRSA = CreateWindowA("edit", "111", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL, 300, 55, 250, 80, hwnd, NULL, NULL, NULL);

	CreateWindowA("button", "Зашифровать", WS_VISIBLE | WS_CHILD, 15, 150, 250, 20, hwnd, reinterpret_cast<HMENU>(OnRSAEncode), NULL, NULL);
	CreateWindowA("button", "Расшифровать", WS_VISIBLE | WS_CHILD, 300, 150, 250, 20, hwnd, reinterpret_cast<HMENU>(OnRSADecode), NULL, NULL);

	CreateWindowA("button", "ВВОД из файла", WS_VISIBLE | WS_CHILD, 15, 180, 250, 20, hwnd, reinterpret_cast<HMENU>(OnRSALoadFromFile), NULL, NULL);
	CreateWindowA("button", "ВЫВОД в файл", WS_VISIBLE | WS_CHILD, 300, 180, 250, 20, hwnd, reinterpret_cast<HMENU>(OnRSAWriteToFile), NULL, NULL);

	CreateWindowA("static", "Число для ключей", WS_VISIBLE | WS_CHILD, 225, 210, 200, 20, hwnd, NULL, NULL, NULL);
	hNKeyRSA = CreateWindowA("edit", " ", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_HSCROLL| ES_NUMBER, 215, 235, 150, 50, hwnd, NULL, NULL, NULL);

	CreateWindowA("static", "Открытый ключ (e, n)", WS_VISIBLE | WS_CHILD, 50, 285, 200, 20, hwnd, NULL, NULL, NULL);
	hOpenKeyRSA = CreateWindowA("edit", " ", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_HSCROLL| ES_NUMBER, 15, 300, 250, 75, hwnd, NULL, NULL, NULL);

	CreateWindowA("static", "Закрытый ключ (d, n)", WS_VISIBLE | WS_CHILD, 350, 285, 200, 20, hwnd, NULL, NULL, NULL);
	hCloseKeyRSA = CreateWindowA("edit", " ", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_HSCROLL| ES_NUMBER, 300, 300, 250, 75, hwnd, NULL, NULL, NULL);
	LoadDataRSA("RSA/n.txt", hNKeyRSA);
	LoadDataRSA("RSA/e.txt", hOpenKeyRSA);
	LoadDataRSA("RSA/d.txt", hCloseKeyRSA);

	CreateWindowA("button", "Сгенерировать пару ключей", WS_VISIBLE | WS_CHILD, 150, 380, 250, 20, hwnd, reinterpret_cast<HMENU>(OnRSAGeneredKey), NULL, NULL);
}





void SaveDataRSA(LPCSTR path, HWND hControlField)
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

void LoadDataRSA(LPCSTR path, HWND hControlField)
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
	ReadFile(FileToLoad, BufferRSA, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(hControlField, BufferRSA);

	CloseHandle(FileToLoad);
}

void ClearBufferRSA(char* buffer)
{
	for (size_t i = 0; i < TextBufferSize; i++)
		buffer[i] = '\0';
}