#pragma once
#include <Windows.h>
#include "Messages.h"

//Виджеты Магический квадрат
void MainWndAddWidgestMSquare(HWND hwnd);

LRESULT CALLBACK SoftwareMainProcedureMSquare(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);