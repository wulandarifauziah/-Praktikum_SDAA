#include <iostream>
using namespace std;

struct HewanPasien
{
    int id;
    char nama[100];
    char jenis[100];
    int umur;
    char keluhan[5000];
    char pemilik[100];
};

int inputID()
{
    int id;
    while (true)
    {
        cout << "Masukkan ID Hewan (angka): ";
        cin >> id;

        if (cin.fail())
        {
            cin.clear();
            cout << "Input ID harus berupa angka!\n";
            system("cls");
        }
        else
        {
            return id;
        }
    }
}

bool cekID(HewanPasien *daftar, int jumlah, int id)
{
    for (int i = 0; i < jumlah; i++)
    {
        if (daftar[i].id == id)
        {
            return true;
        }
    }
    return false;
}

void tambahHewan(HewanPasien *daftar, int *jumlah)
{
    system("cls");
    HewanPasien baru;

    while (true)
    {
        baru.id = inputID();
        if (cekID(daftar, *jumlah, baru.id))
        {
            cout << "ID Hewan sudah ada! Silakan masukkan ID lain.\n";
        }
        else
        {
            break;
        }
    }

    cout << "Masukkan Nama Hewan: ";
    cin >> baru.nama;

    cout << "Masukkan Jenis Hewan: ";
    cin >> baru.jenis;

    cout << "Masukkan Umur Hewan (dalam waktu bulan): ";
    cin >> baru.umur;

    cout << "Masukkan Keluhan Hewan: ";
    cin.ignore();
    cin.getline(baru.keluhan, 100);

    cout << "Masukkan Nama Pemilik: ";
    cin.getline(baru.pemilik, 50);

    daftar[*jumlah] = baru;
    (*jumlah)++;
}

void tampilkanSemuaHewan(HewanPasien *daftar, int jumlah)
{
    system("cls");
    if (jumlah == 0)
    {
        cout << "Tidak ada data hewan pasien yang tersedia.\n";
        return;
    }

    for (int i = 0; i < jumlah; i++)
    {
        cout << "|=================================================================|\n";
        cout << "|                    Riwayat Pasien Klinik Hewan                  |\n";
        cout << "|                             Anabul Care                         |\n";
        cout << "|=================================================================|\n";
        cout << "              ID Hewan      : " << daftar[i].id << "\n";
        cout << "              Nama Hewan    : " << daftar[i].nama << "\n";
        cout << "              Jenis Hewan   : " << daftar[i].jenis << "\n";
        cout << "              Umur Hewan    : " << daftar[i].umur << " bulan\n";
        cout << "              Keluhan       : " << daftar[i].keluhan << "\n";
        cout << "              Pemilik       : " << daftar[i].pemilik << "\n";
        cout << "|=================================================================|\n\n";
    }
}

void cariHewan(HewanPasien *daftar, int jumlah, int id)
{
    system("cls");
    bool ditemukan = false;
    for (int i = 0; i < jumlah; i++)
    {
        if (daftar[i].id == id)
        {
            cout << "|=================================================================|\n";
            cout << "|                        Data Pasien                              |\n";
            cout << "|=================================================================|\n";
            cout << "                  ID Hewan     : " << daftar[i].id << "\n";
            cout << "                  Nama Hewan   : " << daftar[i].nama << "\n";
            cout << "                  Jenis Hewan  : " << daftar[i].jenis << "\n";
            cout << "                  Umur Hewan   : " << daftar[i].umur << " bulan\n";
            cout << "                  Keluhan      : " << daftar[i].keluhan << "\n";
            cout << "                  Pemilik      : " << daftar[i].pemilik << "\n";
            cout << "|=================================================================|\n"
                 << endl;
            ditemukan = true;
            cin.ignore();
            break;
        }
    }
    if (!ditemukan)
    {
        cout << "Hewan dengan ID " << id << " tidak ditemukan.\n";
    }
}

void hapusHewan(HewanPasien *daftar, int *jumlah, int id)
{
    system("cls");

    bool ditemukan = false;
    for (int i = 0; i < *jumlah; i++)
    {
        if (daftar[i].id == id)
        {
            for (int j = i; j < *jumlah - 1; j++)
            {
                daftar[j] = daftar[j + 1];
            }
            (*jumlah)--;
            ditemukan = true;
            cout << "Hewan dengan ID " << id << " berhasil dihapus.\n";
            break;
        }
    }
    if (!ditemukan)
    {
        cout << "Hewan dengan ID " << id << " tidak ditemukan.\n";
    }
}

int main()
{
    HewanPasien daftar[200];
    int pilihan;
    int cariId;
    int jumlah = 0;

    do
    {
        system("cls");
        cout << "=====================================\n";
        cout << "| Selamat Datang di Klinik Hewan KH |\n";
        cout << "|           Anabul Care             |\n";
        cout << "=====================================\n";
        cout << "|  1. Tambah Hewan Pasien           |\n";
        cout << "|  2. Tampilkan Semua Pasien        |\n";
        cout << "|  3. Cari Hewan Pasien             |\n";
        cout << "|  4. Hapus Hewan Pasien            |\n";
        cout << "|  5. Keluar                        |\n";
        cout << "=====================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            tambahHewan(daftar, &jumlah);
            break;
        case 2:
            tampilkanSemuaHewan(daftar, jumlah);
            break;
        case 3:
            cariId = inputID();
            cariHewan(daftar, jumlah, cariId);
            break;
        case 4:
            tampilkanSemuaHewan(daftar, jumlah);
            cariId = inputID();
            hapusHewan(daftar, &jumlah, cariId);
            cin.ignore();
            break;
        case 5:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
            break;
        }

        if (pilihan != 5)
        {
            cout << "Tekan Enter untuk melanjutkan...";
            cin.get();
        }

    } while (pilihan != 5);

    return 0;
}
