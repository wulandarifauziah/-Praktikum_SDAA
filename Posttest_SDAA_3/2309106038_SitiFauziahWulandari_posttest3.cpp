#include <iostream>
#include <cstring>

using namespace std;

struct HewanPasien
{
    int id;
    char nama[100];
    char jenis[100];
    int umur;
    char keluhan[5000];
    char pemilik[100];
    HewanPasien *next;
};

HewanPasien *head = nullptr;

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
            cin.ignore(1000, '\n');
            cout << "Input ID harus berupa angka!\n";
        }
        else
        {
            cin.ignore(1000, '\n');
        }
    }
}

int inputUmur()
{
    int umur;
    while (true)
    {
        cout << "Masukkan Umur Hewan (angka dalam bulan): ";
        cin >> umur;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input Umur harus berupa angka!\n";
        }
        else
        {
            cin.ignore(1000, '\n');
            return umur;
        }
    }
}

bool cekID(HewanPasien *head, int id)
{
    HewanPasien *current = head;
    while (current != nullptr)
    {
        if (current->id == id)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

void tambahHewan()
{
    system("cls");
    HewanPasien *baru = new HewanPasien();

    while (true)
    {
        baru->id = inputID();
        if (cekID(head, baru->id))
        {
            cout << "ID Hewan sudah ada! Silakan masukkan ID lain.\n";
        }
        else
        {
            break;
        }
    }

    cout << "Masukkan Nama Hewan: ";
    cin.getline(baru->nama, 100);

    cout << "Masukkan Jenis Hewan: ";
    cin.getline(baru->jenis, 100);

    baru->umur = inputUmur();

    cout << "Masukkan Keluhan Hewan: ";
    cin.getline(baru->keluhan, 5000);

    cout << "Masukkan Nama Pemilik: ";
    cin.getline(baru->pemilik, 100);

    baru->next = head;
    head = baru;

    cout << "Hewan berhasil ditambahkan.\n";
}

void tampilkanSemuaHewan()
{
    system("cls");

    if (head == nullptr)
    {
        cout << "Tidak ada data hewan pasien yang tersedia.\n";
        return;
    }

    HewanPasien *current = head;
    while (current != nullptr)
    {
        cout << "|=================================================================|\n";
        cout << "|                    Riwayat Pasien Klinik Hewan                  |\n";
        cout << "|                             Anabul Care                         |\n";
        cout << "|=================================================================|\n";
        cout << "              ID Hewan      : " << current->id << "\n";
        cout << "              Nama Hewan    : " << current->nama << "\n";
        cout << "              Jenis Hewan   : " << current->jenis << "\n";
        cout << "              Umur Hewan    : " << current->umur << " bulan\n";
        cout << "              Keluhan       : " << current->keluhan << "\n";
        cout << "              Pemilik       : " << current->pemilik << "\n";
        cout << "|=================================================================|\n\n";
        current = current->next;
    }
}

void cariHewan(int id)
{
    system("cls");

    HewanPasien *current = head;
    bool ditemukan = false;

    while (current != nullptr)
    {
        if (current->id == id)
        {
            cout << "|=================================================================|\n";
            cout << "|                        Data Pasien                              |\n";
            cout << "|=================================================================|\n";
            cout << "                  ID Hewan     : " << current->id << "\n";
            cout << "                  Nama Hewan   : " << current->nama << "\n";
            cout << "                  Jenis Hewan  : " << current->jenis << "\n";
            cout << "                  Umur Hewan   : " << current->umur << " bulan\n";
            cout << "                  Keluhan      : " << current->keluhan << "\n";
            cout << "                  Pemilik      : " << current->pemilik << "\n";
            cout << "|=================================================================|\n"
                 << endl;
            ditemukan = true;
            break;
        }
        current = current->next;
    }

    if (!ditemukan)
    {
        cout << "Hewan dengan ID " << id << " tidak ditemukan.\n";
    }
}

void hapusHewan(int id)
{
    system("cls");

    if (head == nullptr)
    {
        cout << "Tidak ada data hewan pasien yang tersedia.\n";
        return;
    }

    HewanPasien *current = head;
    HewanPasien *prev = nullptr;
    bool ditemukan = false;

    while (current != nullptr)
    {
        if (current->id == id)
        {
            ditemukan = true;
            if (prev == nullptr)
            {

                head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            delete current;
            cout << "Hewan dengan ID " << id << " berhasil dihapus.\n";
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!ditemukan)
    {
        cout << "Hewan dengan ID " << id << " tidak ditemukan.\n";
    }
}

int main()
{
    int pilihan;
    int cariId;

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
            tambahHewan();
            break;
        case 2:
            tampilkanSemuaHewan();
            break;
        case 3:
            cariId = inputID();
            cariHewan(cariId);
            break;
        case 4:
            tampilkanSemuaHewan();
            cariId = inputID();
            hapusHewan(cariId);
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
