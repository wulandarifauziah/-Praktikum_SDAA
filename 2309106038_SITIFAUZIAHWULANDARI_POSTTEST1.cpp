#include <iostream>
using namespace std;

int segitiga_pascal(int baris, int posisi)
{
    if ((posisi == 0) || (posisi == baris))
        return 1;
    else
        return segitiga_pascal(baris - 1, posisi) + segitiga_pascal(baris - 1, posisi - 1);
}

int main()
{
    int baris, posisi;
    int i, j;
    cout << "======================================" << endl;
    cout << "Program C++ Segitiga Pascal Siku-Siku" << endl;
    cout << "======================================" << endl;
    cout << endl;

    int tinggi_segitiga = 3;
    cout << "Tinggi segitiga: " << tinggi_segitiga << endl;
    cout << endl;

    for (int i = 0; i < tinggi_segitiga; i++)
    {
        for (int j = 0; j <= i; j++)
            cout << segitiga_pascal(i, j) << " ";

        cout << endl;
    }

    return 0;
}