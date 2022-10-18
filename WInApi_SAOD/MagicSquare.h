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

/**
    * Шифрует заданную строку\слово
    * @param word - строка|слово, которая(-ое) шифруется.
    * @param magic[4][4] - магичекий квадрат.
    * @param size - размер магического квадрата.
    * @return Возвращает зашифрованную строку|слово.
*/
string MSencode(const string& word, const size_t magic[8][8]);

/**
    * Рашифровывает по магическому квадрату
    * @param word - строка|слово, которая(-ое) расшифровывается.
    * @param magic[4][4] - магичекий квадрат.
    * @param size - размер магического квадрата.
    * @return Возвращает расшифрованную строку|слово.
*/
string MSdecode(const string& word, const size_t magic[8][8]);

/*
*   @param choose - отвечает за выбор.
*   @param     1 - Зашифровать сообщение
*   @param     2 - Расшифровать сообщение
*   @param     3 - Вывести матрицу/ключ в файл
*   @param     4 - Заполнить магический квадрат из файла и вывести квадрат в файл
*/
void MainMSquareCrypto(int choose);