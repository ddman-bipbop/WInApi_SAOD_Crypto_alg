#include "WindowTest.h"
#include "Test.h"

char BufferTest[TextBufferSize];

//сохранение в файл текста
void SaveDataTest(LPCSTR path, HWND hControlField);
//чтение из файла текста
void LoadDataTest(LPCSTR path, HWND hControlField);
//Очищает буффер
void ClearBufferTest(char* buffer);

HWND hQuestField;
HWND hNumberOfQuestion;
HWND hWriteCheckAns;

int i = 0;
unsigned num;


LRESULT CALLBACK SoftwareMainProcedureTest(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	switch (msg)
	{
		case WM_CREATE:
			InizializTest();
			MainWndAddWidgestTest(hwnd);
			LoadDataTest("Test/Test.txt", hQuestField);
			break;
		case WM_COMMAND:
			switch (wp)
			{
				case OnTestCheckAns: 
				{
					num = GetDlgItemInt(hwnd, NumberInTest, FALSE, FALSE);
					int TrueAns = 0;
					if (questions[i].check_answer(num))
					{
						TrueAns++;
						MessageBoxA(hwnd, "Верно!", "Message", MB_OK);
					}
					else
					{
						TrueAns++;
						MessageBoxA(hwnd, "Не верно!\nПожалуйста, внимательно изучите теорию. Нужную документацию вы cможете найти, нажав в главном окне на кнопку 'Теория'.", "Message", MB_OK);
					}
					i++;

					if (i == countQuest) {
						int mark = TrueAns / 2;
						if (TrueAns == 0 || (TrueAns >= 5 && TrueAns <= 10))
							MessageBoxA(hwnd, ("Вы ответили правильно на " + to_string(TrueAns) + " вопросов из 10\nВаша оценка: " + to_string(mark)).c_str(), "Message", MB_OK);
						else if (TrueAns == 1)
							MessageBoxA(hwnd, ("Вы ответили правильно на " + to_string(TrueAns) + " вопрос из 10\nВаша оценка: " + to_string(mark)).c_str(), "Message", MB_OK);
						else
							MessageBoxA(hwnd, ("Вы ответили правильно на " + to_string(TrueAns) + " вопроса из 10\nВаша оценка: " + to_string(mark)).c_str(), "Message", MB_OK);
						DestroyWindow(hwnd);
						i = 0;
						TrueAns = 0;
					}
					else {
						SetWindowTextA(hWriteCheckAns, "");
						SetWindowTextA(hNumberOfQuestion, ("Вопрос № " + to_string(i + 1)).c_str());
					}
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

void MainWndAddWidgestTest(HWND hwnd)
{
	hQuestField = CreateWindowA("edit", "111", WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE | WS_HSCROLL, 5, 5, 870, 360, hwnd, NULL, NULL, NULL);
	
	hNumberOfQuestion = CreateWindowA("static", ("Вопрос № " + to_string(i + 1)).c_str(), WS_VISIBLE | WS_CHILD, 330, 385, 90, 30, hwnd, NULL, NULL, NULL);
	hWriteCheckAns = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | ES_NUMBER, 415, 380, 25, 25, hwnd, reinterpret_cast<HMENU>(NumberInTest), NULL, NULL);
	CreateWindowA("button", "Проверить", WS_VISIBLE | WS_CHILD, 325, 415, 200, 20, hwnd, reinterpret_cast<HMENU>(OnTestCheckAns), NULL, NULL);
}

void SaveDataTest(LPCSTR path, HWND hControlField)
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

void LoadDataTest(LPCSTR path, HWND hControlField)
{
	setlocale(LC_ALL, "rus");
	HANDLE FileToLoad = CreateFileA(
		path,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	DWORD bytesIterated;
	ReadFile(FileToLoad, BufferTest, TextBufferSize, &bytesIterated, NULL);

	SetWindowTextA(hControlField, BufferTest);

	CloseHandle(FileToLoad);
}

void ClearBufferTest(char* buffer)
{
	for (size_t i = 0; i < TextBufferSize; i++)
		buffer[i] = '\0';
}