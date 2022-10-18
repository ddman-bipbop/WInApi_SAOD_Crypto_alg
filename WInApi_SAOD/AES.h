#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <wincrypt.h>
#include <bcrypt.h>
#include <string.h>
#include <iostream>
#include <tchar.h>
#include <io.h>
#include <vector>
#include <fstream>
#include <stdio.h>
#pragma warning(disable: 4018)

typedef unsigned long type;
using namespace std;

//Генерация пароля
void GeneratedPass();

//Зашифровать сообщение
void EncodeAES();

void DecodeAES();