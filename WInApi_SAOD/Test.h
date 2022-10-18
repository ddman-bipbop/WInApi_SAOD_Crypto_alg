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

//Инициализация теста
void InizializTest() 
{
    questions[0].question = "Вопрос 1. Обратимое преобразование информации в целях сокрытия от неавторизованных лиц, с предоставлением, в это же время, авторизованным пользователям доступа к ней:\n";
    questions[0].var_answers = "\t1 - шифрование\n\t2 - зашифровка\n\t3 - закрытость\n";
    questions[0].answer = 1;

    questions[1].question = "Вопрос 2. Сколько лет назад появилось шифрование:\n";
    questions[1].var_answers = "\t1 - три тысячи лет назад\n\t2 - четыре тысячи лет назад\n\t3 - шесть тысяч лет назад\n";
    questions[1].answer = 2;

    questions[2].question = "Вопрос 3. Первое известное применение шифра:\n";
    questions[2].var_answers = "\t1 - индийский текст\n\t2 - русский текст\n\t3 - египетский текст\n";
    questions[2].answer = 3;

    questions[3].question = "Вопрос 4. Какое ещё определение можно дать шифрованию:\n";
    questions[3].var_answers = "\t1 - преобразовательный процесс исходного текста в зашифрованный\n\t2 - упорядоченный набор из элементов алфавита\n\t3 - неупорядоченный набор из элементов алфавита\n";
    questions[3].answer = 1;

    questions[4].question = "Вопрос 5. Что такое дешифрование:\n";
    questions[4].var_answers = "\t1 - пароли для доступа к сетевым ресурсам\n\t2 - сертификаты для доступа к сетевым ресурсам и зашифрованным данным на самом компьютере\n\t3 - на основе ключа шифрованный текст преобразуется в исходный\n";
    questions[4].answer = 3;

    questions[5].question = "Вопрос 6. Пользователи являются авторизованными, если они обладают определённым:\n";
    questions[5].var_answers = "\t1 - математическим ключом\n\t2 - аутентичным ключом\n\t3 - паролем\n";
    questions[5].answer = 2;

    questions[6].question = "Вопрос 7. Одно из составляющих шифрования:\n";
    questions[6].var_answers = "\t1 - перешифровка\n\t2 - запечатывание\n\t3 - зашифровывание\n";
    questions[6].answer = 3;

    questions[7].question = "Вопрос 8. Одно из состояний безопасности информации:\n";
    questions[7].var_answers = "\t1 - доступность\n\t2 - открытость\n\t3 - конфиденциальность\n";
    questions[7].answer = 3;

    questions[8].question = "Вопрос 9. Одно из состояний безопасности информации:\n";
    questions[8].var_answers = "\t1 - раздробленность\n\t2 - целостность\n\t3 - частичность\n";
    questions[8].answer = 2;

    questions[9].question = "Вопрос 10. Шифрование, которое используется для скрытия информации от неавторизованных пользователей при передаче или при хранении:\n";
    questions[9].var_answers = "\t1 - идентифицируемость\n\t2 - конфиденциальность\n\t3 - целостность\n";
    questions[9].answer = 2;
    ofstream outTest("Test/Test.txt", ios::out);
    for (size_t i = 0; i < countQuest; ++i)
    {
        outTest << questions[i].question;
        outTest << questions[i].var_answers;
    }

    outTest.close();
}