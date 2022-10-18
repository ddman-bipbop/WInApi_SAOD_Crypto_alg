#pragma once
#include <Windows.h>
#include "Messages.h"

//Виджеты Магический квадрат
void MainWndAddWidgestT(HWND hwnd);

LRESULT CALLBACK SoftwareMainProcedureT(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);