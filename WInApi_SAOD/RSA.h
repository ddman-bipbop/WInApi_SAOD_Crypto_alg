#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <io.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include <cstdint>
#include <vector>
#include <fstream> // работа с файлами
using namespace std;

int Exgcd(int m, int n, int& x);

int ProducePrimeNumber(int prime[]);

void RSA_Initialize();

int BianaryTransform(int num, int bin_num[]);

long long Modular_Exonentiation(long long a, int b, int n);

void RSA_Encrypt();

void RSA_Decrypt();