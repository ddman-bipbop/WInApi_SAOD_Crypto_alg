#include "MagicSquare.h"

string MSencode(const string& word, const size_t magic[8][8])
{
    string result;
    string::value_type encoded[8][8] = {};

    // обнуление массива под результат
    for (size_t i = 0; i < 8; ++i) {
        for (size_t j = 0; j < 8; ++j)
            encoded[i][j] = '\0';
    }

    for (size_t i = 0; i < 8; ++i)
        for (size_t j = 0; j < 8; ++j) {
            if (magic[i][j] <= word.length()) {
                encoded[i][j] = word[magic[i][j] - 1];
            }
        }
    result.clear();
    for (size_t i = 0; i < 8; ++i)
        for (size_t j = 0; j < 8; ++j)
            if (0 != encoded[i][j])
                result.push_back(encoded[i][j]);
    return result;
}

string MSdecode(const string& word, const size_t magic[8][8])
{
    string result;
    size_t current;

    result.resize(word.length());
    current = 0;
    for (size_t i = 0; i < 8; ++i)
        for (size_t j = 0; j < 8; ++j) {
            if (magic[i][j] <= word.length()) {
                result[magic[i][j] - 1] = word[current];
                ++current;
                if (current == word.length())
                    goto last;
            }
        }
last:
    return result;
}

void MainMSquareCrypto(int choose)
{
    string word, result;
    string buffer;

    const size_t MSsize = 8;
    size_t squadre[MSsize][MSsize] = { //Магический квадрат
       { 1,  2, 32, 31, 50, 49, 47, 48},
       { 3,  4, 30, 29, 52, 51, 45, 56},
       {56, 55, 41, 42,  7,  8, 26, 25},
       {54, 53, 43, 44,  5,  6, 28, 27},
       {15, 16, 18, 17, 64, 63, 33, 34},
       {13, 14, 20, 19, 62, 61, 35, 36},
       {58, 57, 39, 40,  9, 10, 24, 23},
       {60, 59, 37, 38, 11, 12, 22, 21}
    };
    if (choose == 3) 
    {
       
        ofstream oFileKey("MagicSquare/keyMSquare.txt", ios::out);
        if (!oFileKey.is_open()) // вызов метода is_open()
        {
            return;
        }
        else
        {
            for (size_t i = 0; i < MSsize; ++i)
            {
                for (size_t j = 0; j < MSsize; ++j) 
                {
                    oFileKey << squadre[i][j]<<"\t";
                }
                oFileKey << endl;
            }
        }
        oFileKey.close();// закрыть файл
        return;
    }
    if (choose == 4) 
    {
        ifstream iFile("MagicSquare/inputKeyMSquare.txt", ios::in);//Читаем из файла
        if (!iFile.is_open()) // вызов метода is_open()
        {
            return;
        }
        else
        {
            ofstream oFileKey("MagicSquare/keyMSquare.txt", ios::out);
            if (!oFileKey.is_open()) // вызов метода is_open()
            {
                return;
            }
            else
            {
                for (size_t i = 0; i < MSsize; ++i)
                {
                    for (size_t j = 0; j < MSsize; ++j)
                    {
                        iFile >> squadre[i][j];
                    }
                }

                for (size_t i = 0; i < MSsize; ++i)
                {
                    for (size_t j = 0; j < MSsize; ++j)
                    {
                        oFileKey << squadre[i][j] << "\t";
                    }
                    oFileKey << endl;
                }
            }
            oFileKey.close();
            
        }
        iFile.close();
        return;
    }

    ifstream iFileKey("MagicSquare/keyMSquare.txt", ios::in);//Читаем из файла
    if (!iFileKey.is_open()) // вызов метода is_open()
    {
        return;
    }
    else
    {
        for (size_t i = 0; i < MSsize; ++i)
        {
            for (size_t j = 0; j < MSsize; ++j)
            {
                iFileKey >> squadre[i][j];
            }
        }
        iFileKey.close();
    }

    ifstream iFile("MagicSquare/tempInCryptoText.txt", ios::in);//Читаем из файла
    if (!iFile.is_open()) // вызов метода is_open()
    {
        return;
    }
    else
    {
        ofstream oFile("MagicSquare/CryptoText.txt", ios::out);
        if (!oFile.is_open()) // вызов метода is_open()
        {
            return;
        }
        else
        {
            while (!iFile.eof()) //пока не конец.
            {

                getline(iFile, buffer); // считываем строку из файла tempInCryptoText.txt
                if(choose==1)
                    result = MSencode(buffer, squadre);// Зашифровать строку
                if (choose == 2)
                    result = MSdecode(buffer, squadre);
                oFile << result << endl;
            }
        }
        oFile.close();// закрыть файл CryptoText.txt
    }
    iFile.close();// закрыть файл tempInCryptoText.txt

}