#include "Windowteory.h"


char BufferTeory[TextBufferSizeForTeory];

//чтение из файла текста
void LoadDataTeory(LPCSTR path, HWND hControlField);
//Очищает буффер
void ClearBufferTeory(char* buffer);

HWND hTeoryField;

LRESULT CALLBACK SoftwareMainProcedureT(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_CREATE:
			MainWndAddWidgestT(hwnd);
			break;
		case WM_COMMAND:
			switch (wp)
			{
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

void MainWndAddWidgestT(HWND hwnd)
{
	hTeoryField = CreateWindowA("edit", " ", WS_VISIBLE | WS_CHILD  | ES_MULTILINE /* | WS_HSCROLL*/ | WS_VSCROLL, 5, 5, 880, 760, hwnd, NULL, NULL, NULL);
	LoadDataTeory("Teory/Teory.txt", hTeoryField);
}

void LoadDataTeory(LPCSTR path, HWND hControlField)
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
	ReadFile(FileToLoad, BufferTeory, TextBufferSizeForTeory, &bytesIterated, NULL);

	SetWindowTextA(hControlField, BufferTeory);

	CloseHandle(FileToLoad);
}

void ClearBufferTeory(char* buffer)
{
	for (size_t i = 0; i < TextBufferSizeForTeory; i++)
		buffer[i] = '\0';
}