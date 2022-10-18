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
#include <fstream> // ������ � �������
using namespace std;

/**
    * ������� �������� ������\�����
    * @param word - ������|�����, �������(-��) ���������.
    * @param magic[4][4] - ��������� �������.
    * @param size - ������ ����������� ��������.
    * @return ���������� ������������� ������|�����.
*/
string MSencode(const string& word, const size_t magic[8][8]);

/**
    * ������������� �� ����������� ��������
    * @param word - ������|�����, �������(-��) ����������������.
    * @param magic[4][4] - ��������� �������.
    * @param size - ������ ����������� ��������.
    * @return ���������� �������������� ������|�����.
*/
string MSdecode(const string& word, const size_t magic[8][8]);

/*
*   @param choose - �������� �� �����.
*   @param     1 - ����������� ���������
*   @param     2 - ������������ ���������
*   @param     3 - ������� �������/���� � ����
*   @param     4 - ��������� ���������� ������� �� ����� � ������� ������� � ����
*/
void MainMSquareCrypto(int choose);