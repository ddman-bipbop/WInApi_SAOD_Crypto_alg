#include "AES.h"

void GeneratedPass()
{
    srand(time(NULL));
    int N=rand()%64;

    char* pass = new char[N + 1]; //выделяем память для строки пароля
    for (int i = 0; i < N; ++i)
    {
        switch (rand() % 3) //генерируем случайное число от 0 до 2
        {
        case 0: //если ноль
            pass[i] = rand() % 10 + '0'; //вставляем в пароль случайную цифру
            break;
        case 1: //если единица
            pass[i] = rand() % 26 + 'A'; //вставляем случайную большую букву
            break;
        case 2: //если двойка
            pass[i] = rand() % 26 + 'a'; //вставляем случайную маленькую букву
        }
    }
    pass[N] = 0; //записываем в конец строки признак конца строки
    ofstream oFileKey("AES/inputKey.txt");
    if (!oFileKey.is_open()) // вызов метода is_open()
    {
        return;
    }
    else
    {
        for (size_t i = 0; i < N; i++)
        {
            oFileKey << pass[i];
        }
        
    }
    oFileKey.close();
}

void EncodeAES()
{
	CHAR pass[65];

    ifstream iFile("AES/inputKey.txt", ios::in);//Читаем из файла
    if (!iFile.is_open()) // вызов метода is_open()
    {
        return;
    }
    else
    {
        iFile >> pass;
    }
    iFile.close();

    HCRYPTPROV hProv; //дескриптор криптопровайдера
    HCRYPTKEY hKey; //дескриптор ключа, созданного из хэш-кода
    HCRYPTHASH hHash; //дескриптор хэш-объекта
    HCRYPTPROV hCryptProv;

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
    {
        std::cout << "Error\n";
        return ;
    }

    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash))
    {
        std::cout << "Error\n";
        CryptReleaseContext(hProv, 0);
        return ;
    }

    if (!CryptHashData(hHash, (BYTE*)pass, strlen(pass), 0))
    {
        std::cout << "Error\n";
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return ;
    }

    if (!CryptDeriveKey(hProv, CALG_AES_192, hHash, CRYPT_EXPORTABLE, &hKey))
    {
        std::cout << "Error\n";
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return ;
    }

    string filein = "AES/tempInCryptoText.txt";
    string fileout1 = "AES/CryptoText.txt";

    std::ifstream ifs(filein, std::ifstream::binary);
    ifs.seekg(0, ifs.end);
    int len = ifs.tellg();
    ifs.seekg(0);

    std::vector<char> data(len + 10240);

    ifs.read(data.data(), len);
    ifs.close();

    DWORD datalen = len;
    if (!CryptEncrypt(hKey, NULL, true, 0, reinterpret_cast<BYTE*>(data.data()), &datalen, data.size()))
    {
        std::cout << "Error\n";
    }
    else
    {
        ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!///
        std::ofstream ofs(fileout1, std::ifstream::binary); //ЗАПИСЫВАЕТ ЗАШИФРОВАННОЕ СООБЩЕНИЕ!!!!!!!!!!!!!!!
        ofs.write(data.data(), datalen);
        ofs.close();
        ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!///
    }

    CryptDestroyHash(hHash);
    CryptDestroyKey(hKey);
    CryptReleaseContext(hProv, 0);
}

void DecodeAES()
{
    CHAR pass[65];

    ifstream iFile("AES/inputKey.txt", ios::in);//Читаем из файла
    if (!iFile.is_open()) // вызов метода is_open()
    {
        return;
    }
    else
    {
        iFile >> pass;
    }
    iFile.close();

    HCRYPTPROV hProv; //дескриптор криптопровайдера
    HCRYPTKEY hKey; //дескриптор ключа, созданного из хэш-кода
    HCRYPTHASH hHash; //дескриптор хэш-объекта
    HCRYPTPROV hCryptProv;

    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_AES, CRYPT_VERIFYCONTEXT))
    {
        std::cout << "Error\n";
        return ;
    }

    if (!CryptCreateHash(hProv, CALG_SHA_256, 0, 0, &hHash))
    {
        std::cout << "Error\n";
        CryptReleaseContext(hProv, 0);
        return ;
    }

    if (!CryptHashData(hHash, (BYTE*)pass, strlen(pass), 0))
    {
        std::cout << "Error\n";
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return ;
    }

    if (!CryptDeriveKey(hProv, CALG_AES_192, hHash, CRYPT_EXPORTABLE, &hKey))
    {
        std::cout << "Error\n";
        CryptDestroyHash(hHash);
        CryptReleaseContext(hProv, 0);
        return ;
    }
    string fileout1 = "AES/tempInCryptoText.txt";
    string fileout2 = "AES/CryptoText.txt";

    std::ifstream ifs(fileout1, std::ifstream::binary);
    ifs.seekg(0, ifs.end);
    int len = ifs.tellg();
    ifs.seekg(0);

    std::vector<char> data(len + 10240);

    ifs.read(data.data(), len);
    ifs.close();

    DWORD datalen = len;
    if (!CryptDecrypt(hKey, NULL, true, 0, reinterpret_cast<BYTE*>(data.data()), &datalen))
    {
        std::cout << "Error\n";
    }
    else
    {
        ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!///
        std::ofstream ofs(fileout2, std::ifstream::binary); //ЗАПИСЫВАЕТ РАСШИФРОВАННОЕ СООБЩЕНИЕ
        ofs.write(data.data(), datalen);
        ofs.close();
        ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!///
    }
    CryptDestroyHash(hHash);
    CryptDestroyKey(hKey);
    CryptReleaseContext(hProv, 0);

}