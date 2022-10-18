#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
#include <Windows.h>
#include <fstream>
using namespace std;

struct Question
{
    string question;
    string var_answers;
    int answer;

    bool check_answer(int num)
    {
        if (answer == num) return true;
        return false;
    }

    
};
const size_t countQuest = 10;
Question questions[countQuest];

//������������� �����
void InizializTest() 
{
    questions[0].question = "������ 1. ��������� �������������� ���������� � ����� �������� �� ���������������� ���, � ���������������, � ��� �� �����, �������������� ������������� ������� � ���:\n";
    questions[0].var_answers = "\t1 - ����������\n\t2 - ����������\n\t3 - ����������\n";
    questions[0].answer = 1;

    questions[1].question = "������ 2. ������� ��� ����� ��������� ����������:\n";
    questions[1].var_answers = "\t1 - ��� ������ ��� �����\n\t2 - ������ ������ ��� �����\n\t3 - ����� ����� ��� �����\n";
    questions[1].answer = 2;

    questions[2].question = "������ 3. ������ ��������� ���������� �����:\n";
    questions[2].var_answers = "\t1 - ��������� �����\n\t2 - ������� �����\n\t3 - ���������� �����\n";
    questions[2].answer = 3;

    questions[3].question = "������ 4. ����� ��� ����������� ����� ���� ����������:\n";
    questions[3].var_answers = "\t1 - ������������������ ������� ��������� ������ � �������������\n\t2 - ������������� ����� �� ��������� ��������\n\t3 - ��������������� ����� �� ��������� ��������\n";
    questions[3].answer = 1;

    questions[4].question = "������ 5. ��� ����� ������������:\n";
    questions[4].var_answers = "\t1 - ������ ��� ������� � ������� ��������\n\t2 - ����������� ��� ������� � ������� �������� � ������������� ������ �� ����� ����������\n\t3 - �� ������ ����� ����������� ����� ������������� � ��������\n";
    questions[4].answer = 3;

    questions[5].question = "������ 6. ������������ �������� ���������������, ���� ��� �������� �����������:\n";
    questions[5].var_answers = "\t1 - �������������� ������\n\t2 - ����������� ������\n\t3 - �������\n";
    questions[5].answer = 2;

    questions[6].question = "������ 7. ���� �� ������������ ����������:\n";
    questions[6].var_answers = "\t1 - ������������\n\t2 - �������������\n\t3 - ��������������\n";
    questions[6].answer = 3;

    questions[7].question = "������ 8. ���� �� ��������� ������������ ����������:\n";
    questions[7].var_answers = "\t1 - �����������\n\t2 - ����������\n\t3 - ������������������\n";
    questions[7].answer = 3;

    questions[8].question = "������ 9. ���� �� ��������� ������������ ����������:\n";
    questions[8].var_answers = "\t1 - ���������������\n\t2 - �����������\n\t3 - �����������\n";
    questions[8].answer = 2;

    questions[9].question = "������ 10. ����������, ������� ������������ ��� ������� ���������� �� ���������������� ������������� ��� �������� ��� ��� ��������:\n";
    questions[9].var_answers = "\t1 - ������������������\n\t2 - ������������������\n\t3 - �����������\n";
    questions[9].answer = 2;
    ofstream outTest("Test/Test.txt", ios::out);
    for (size_t i = 0; i < countQuest; ++i)
    {
        outTest << questions[i].question;
        outTest << questions[i].var_answers;
    }

    outTest.close();
}