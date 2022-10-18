#include "ElGamal.h"

int power(int a, int b, int n) {// a^b mod n
    int tmp = a;
    int sum = tmp;
    for (int i = 1; i < b; i++) {
        for (int j = 1; j < a; j++) {
            sum += tmp;
            if (sum >= n) {
                sum -= n;
            }
        }
        tmp = sum;
    }
    return tmp;
}

int mul(int a, int b, int n) {// a*b mod n
    int sum = 0;

    for (int i = 0; i < b; i++) {
        sum += a;

        if (sum >= n) {
            sum -= n;
        }
    }

    return sum;
}
void key() 
{
    int p = 0, g = 0, x = 0;
    ifstream inP("ElGamal/p.txt", ios::in);
    inP >> p;
    inP.close();

    ifstream inG("ElGamal/g.txt", ios::in);
    inG >> g;
    inG.close();

    ifstream inX("ElGamal/x.txt", ios::in);
    inX >> x;
    inX.close();

    int y = power(g, x, p);

    ofstream outY("ElGamal/y.txt", ios::out);
    outY << y;
    outY.close();

    ofstream outKey("ElGamal/key.txt", ios::out);

    outKey << p << " " << g << " " << y;
    outKey.close();
}
void crypt(string inFileName, string outFileName) {
    srand(time(NULL));
    ifstream inf(inFileName,ios::in);
    ofstream outf(outFileName, ios::out);

    int p = 0;
    int g = 0; 
    int x = 0; 
    int y = 0;

    ifstream inP("ElGamal/p.txt", ios::in);
    inP >> p;
    inP.close();

    ifstream inG("ElGamal/g.txt", ios::in);
    inG >> g;
    inG.close();

    ifstream inX("ElGamal/x.txt", ios::in);
    inX >> x;
    inX.close();

    y = power(g, x, p);
    /*ifstream inY("ElGamal/x.txt", ios::in);
    inY >> y;
    inY.close();*/

    //wcout << "Открытый ключ (p,g,y)=" << "(" << p << "," << g << "," << y << ")" << endl;
    //wcout << "Закрытый ключ x=" << x << endl;

    //wcout << "\nШифруемый текст:" << endl;

    while (inf.good()) {
        int m = inf.get();
        if (m > 0) {
            wcout << (char)m;

            int k = rand() % (p - 2) + 1; // 1 < k < (p-1)
            int a = power(g, k, p);
            int b = mul(power(y, k, p), m, p);
            outf << a << " " << b << " ";
        }
    }

    wcout << endl;

    inf.close();
    outf.close();
}

void decrypt(string inFileName, string outFileName) {
    ifstream inf(inFileName.c_str());
    ofstream outf(outFileName.c_str());

    int p= 0, x = 0;
    ifstream inP("ElGamal/p.txt", ios::in);
    inP >> p;
    inP.close();

    ifstream inX("ElGamal/x.txt", ios::in);
    inX >> x;
    inX.close();

    //wcout << "\nДешифрованый текст:" << endl;

    while (inf.good()) {
        int a = 0;
        int b = 0;
        inf >> a;
        inf >> b;

        if (a != 0 && b != 0) {
            //wcout<<a<<" "<<b<<endl;

            int deM = mul(b, power(a, p - 1 - x, p), p);// m=b*(a^x)^(-1)mod p =b*a^(p-1-x)mod p - трудно было  найти нормальную формулу, в ней вся загвоздка
            char m = static_cast<char>(deM);
            outf << m;
            //wcout << m;
        }
    }

    //wcout << endl;

    inf.close();
    outf.close();
}