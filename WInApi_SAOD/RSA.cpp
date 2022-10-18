#include "RSA.h"

int Exgcd(int m, int n, int& x)
{
    int x1, y1, x0, y0, y;
    x0 = 1; y0 = 0;
    x1 = 0; y1 = 1;
    x = 0; y = 1;
    int r = m % n;
    int q = (m - r) / n;
    while (r)
    {
        x = x0 - q * x1; y = y0 - q * y1;
        x0 = x1; y0 = y1;
        x1 = x; y1 = y;
        m = n; n = r; r = m % n;
        q = (m - r) / n;
    }
    return n;
}

int ProducePrimeNumber(int prime[])
{
    int c = 0, vis[1001];
    memset(vis, 0, sizeof(vis));
    for (int i = 2; i <= 1000; i++)if (!vis[i])
    {
        prime[c++] = i;
        for (int j = i * i; j <= 1000; j += i)
            vis[j] = 1;
    }

    return c;
}

void RSA_Initialize()
{
    int n, e = 0, d=0;
    // Вынимаем простые числа в пределах 1000 и сохраняем их в массиве prime []
    int prime[5000];
    int count_Prime = ProducePrimeNumber(prime);

    // Случайно возьмем два простых числа p, q
    srand((unsigned)time(NULL));
    int ranNum1 = rand() % count_Prime;
    int ranNum2 = rand() % count_Prime;
    int p = prime[ranNum1], q = prime[ranNum2];

    n = p * q;

    int On = (p - 1) * (q - 1);


    // Используем расширенный алгоритм Евклида, чтобы найти e, d
    for (int j = 3; j < On; j += 1331)
    {
        int gcd = Exgcd(j, On, d);
        if (gcd == 1 && d > 0)
        {
            e = j;
            break;
        }

    }
    ofstream oNf("RSA/n.txt", ios::out);
    oNf << n;
    oNf.close();

    ofstream oDf("RSA/d.txt", ios::out);
    oDf << d;
    oDf.close();

    ofstream oEf("RSA/e.txt", ios::out);
    oEf << e;
    oEf.close();
}

int BianaryTransform(int num, int bin_num[])
{

    int i = 0, mod = 0;

    // Преобразуется в двоичный, обратный временно сохраняется в массиве temp []
    while (num != 0)
    {
        mod = num % 2;
        bin_num[i] = mod;
        num = num / 2;
        i++;
    }

    // Возвращает количество цифр в двоичных числах
    return i;
}

long long Modular_Exonentiation(long long a, int b, int n)
{
    int c = 0, bin_num[1000];
    long long d = 1;
    int k = BianaryTransform(b, bin_num) - 1;

    for (int i = k; i >= 0; i--)
    {
        c = 2 * c;
        d = (d * d) % n;
        if (bin_num[i] == 1)
        {
            c = c + 1;
            d = (d * a) % n;
        }
    }
    return d;
}

void RSA_Encrypt()
{
    int Plaintext[1000]; // Открытый текст
    long long Ciphertext[1000]; // Зашифрованный текст
    
    int e = 0, n = 0;

    ifstream oFileN("RSA/n.txt", ios::in);
    oFileN >> n;
    oFileN.close();

    ifstream oFileE("RSA/e.txt", ios::in);
    oFileE >> e;
    oFileE.close();
    

    ifstream iFileInput("RSA/tempInCryptoText.txt",ios::in);
    size_t i = 0;
    while (!iFileInput.eof())
    {
        iFileInput >> Plaintext[i];
        i++;
    }
    int N = i;
    iFileInput.close();
    
    
    for (size_t i = 0; i < N; ++i)
        Ciphertext[i] = Modular_Exonentiation(Plaintext[i], e, n);

    ofstream oFileCrypto("RSA/CryptoText.txt", ios::out);
    for (size_t i = 0; i < N; ++i)
    {
        oFileCrypto << Ciphertext[i]<<" ";
    }

    oFileCrypto.close();
}

void RSA_Decrypt()
{
    int Plaintext[1000]; // Открытый текст
    long long Ciphertext[1000]; // Зашифрованный текст

    int d = 0, n = 0;

    ifstream oFileN("RSA/n.txt", ios::in);
    oFileN >> n;
    oFileN.close();

    ifstream oFileD("RSA/d.txt", ios::in);
    oFileD >> d;
    oFileD.close();

    ifstream iFileInput("RSA/tempInCryptoText.txt", ios::in);
    size_t i = 0;
    while (!iFileInput.eof())
    {
        iFileInput >> Plaintext[i];
        ++i;
    }
    int N = i-1;
    iFileInput.close();
    
    for (size_t i = 0; i < N; i++)
        Ciphertext[i] = Modular_Exonentiation(Plaintext[i], d, n);

    ofstream oFileCrypto("RSA/CryptoText.txt", ios::out);
    for (size_t i = 0; i < N; ++i)
    {
        oFileCrypto << Ciphertext[i] << " ";
    }

    oFileCrypto.close();
}