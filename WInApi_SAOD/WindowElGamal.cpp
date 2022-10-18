#include "WindowElGamal.h"
#include "ElGamal.h"

char BufferElGamal[TextBufferSize];

//сохранение в файл текста
void SaveDataElGamal(LPCSTR path, HWND hControlField);
//чтение из файла текста
void LoadDataElGamal(LPCSTR path, HWND hControlField);
//Очищает буффер
void ClearBufferElGamal(char* buffer);

HWND hReadControlElGamal;
HWND hWriteControlElGamal;
HWND hOpenKey;
HWND hCloseKey;

LRESULT CALLBACK SoftwareMainProcedureElGamal(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
	case WM_CREATE:
		MainWndAddWidgestElGamal(hwnd);

		break;
	case WM_COMMAND:
		switch (wp)
		{
		case OnELGamalEncode:
		{
			ClearBufferElGamal(BufferElGamal);
			SetWindowTextA(hWriteControlElGamal, "");
			GetWindowTextA(hReadControlElGamal, BufferElGamal, TextBufferSize); // считывает текст из поля ВВОД
			SaveDataElGamal("ElGamal/tempInCryptoText.txt", hReadControlElGamal); //сохранение текста из поля ВВОД в файл
			crypt("ElGamal/tempInCryptoText.txt","ElGamal/CryptoText.txt");
			ClearBufferElGamal(BufferElGamal);
			LoadDataElGamal("ElGamal/CryptoText.txt", hWriteControlElGamal);

			break;
		}
		case OnElGamalDecode: 
		{
			ClearBufferElGamal(BufferElGamal);
			SetWindowTextA(hWriteControlElGamal, "");
			GetWindowTextA(hReadControlElGamal, BufferElGamal, TextBufferSize); // считывает текст из поля ВВОД
			SaveDataElGamal("ElGamal/tempInCryptoText.txt", hReadControlElGamal); //сохранение текста из поля ВВОД в файл
			decrypt("ElGamal/tempInCryptoText.txt", "ElGamal/CryptoText.txt");
			ClearBufferElGamal(BufferElGamal);
			LoadDataElGamal("ElGamal/CryptoText.txt", hWriteControlElGamal);

			break;
		}
		case OnElGamalLoadFromFile:
		{
			ClearBufferElGamal(BufferElGamal);
			SetWindowTextA(hReadControlElGamal, "");
			LoadDataElGamal("ElGamal/input.txt", hReadControlElGamal);
			break;
		}
		case OnElGamalWriteToFile:
		{
			SaveDataElGamal("ElGamal/output.txt", hWriteControlElGamal);
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
void MainWndAddWidgestElGamal(HWND hwnd)
{
	CreateWindowA("static", "ВВОД", WS_VISIBLE | WS_CHILD, 100, 15, 100, 20, hwnd, NULL, NULL, NULL);
	CreateWindowA("static", "ВЫВОД", WS_VISIBLE | WS_CHILD, 400, 15, 100, 20, hwnd, NULL, NULL, NULL);

	hReadControlElGamal = CreateWindowA("edit", "111", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL, 15, 55, 250, 80, hwnd, NULL, NULL, NULL);
	hWriteControlElGamal = CreateWindowA("edit", "111", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL, 300, 55, 250, 80, hwnd, NULL, NULL, NULL);

	CreateWindowA("button", "Зашифровать", WS_VISIBLE | WS_CHILD, 15, 150, 250, 20, hwnd, reinterpret_cast<HMENU>(OnELGamalEncode), NULL, NULL);
	CreateWindowA("button", "Расшифровать", WS_VISIBLE | WS_CHILD, 300, 150, 250, 20, hwnd, reinterpret_cast<HMENU>(OnElGamalDecode), NULL, NULL);

	CreateWindowA("button", "ВВОД из файла", WS_VISIBLE | WS_CHILD, 15, 180, 250, 20, hwnd, reinterpret_cast<HMENU>(OnElGamalLoadFromFile), NULL, NULL);
	CreateWindowA("button", "ВЫВОД в файл", WS_VISIBLE | WS_CHILD, 300, 180, 250, 20, hwnd, reinterpret_cast<HMENU>(OnElGamalWriteToFile), NULL, NULL);

	CreateWindowA("static", "Открытый ключ (p, g, y)", WS_VISIBLE | WS_CHILD, 50, 250, 200, 20, hwnd, NULL, NULL, NULL);
	hOpenKey = CreateWindowA("edit", " ", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_HSCROLL, 15, 275, 250, 100, hwnd, NULL, NULL, NULL);
	key();
	LoadDataElGamal("ElGamal/key.txt", hOpenKey);
	

	CreateWindowA("static", "Закрытый ключ (x)", WS_VISIBLE | WS_CHILD, 350, 250, 200, 20, hwnd, NULL, NULL, NULL);
	hCloseKey = CreateWindowA("edit", " ", WS_VISIBLE | WS_CHILD | ES_MULTILINE | WS_HSCROLL | ES_NUMBER, 300, 275, 250, 100, hwnd, NULL, NULL, NULL);
	ClearBufferElGamal(BufferElGamal);
	LoadDataElGamal("ElGamal/x.txt", hCloseKey);

	//CreateWindowA("button", "Сгенерировать пару ключей", WS_VISIBLE | WS_CHILD, 150, 380, 250, 20, hwnd, reinterpret_cast<HMENU>(OnRSAGeneredKey), NULL, NULL);
}

void SaveDataElGamal(LPCSTR path, HWND hControlField)
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

void LoadDataElGamal(LPCSTR path, HWND hControlField)
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
	ReadFile(FileToLoad, BufferElGamal, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(hControlField, BufferElGamal);

	CloseHandle(FileToLoad);
}

void ClearBufferElGamal(char* buffer)
{
	for (size_t i = 0; i < TextBufferSize; i++)
		buffer[i] = '\0';
}