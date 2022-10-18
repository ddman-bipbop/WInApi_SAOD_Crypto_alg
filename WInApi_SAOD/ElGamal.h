#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#pragma hdrstop// ѕредоставл€ет дополнительный элемент управлени€ по именам файлов предварительной компил€ции и над местоположением на котором сохран€етс€ состо€ние компил€ции
using namespace std;

// a^b mod n
int power(int a, int b, int n);

// a*b mod n
int mul(int a, int b, int n);

void key();

void crypt(string inFileName, string outFileName);

void decrypt(string inFileName, string outFileName);