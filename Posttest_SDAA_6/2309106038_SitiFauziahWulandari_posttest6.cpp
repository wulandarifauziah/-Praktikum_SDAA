#include <iostream>
#include <cstring>
#include <cmath>  // Untuk sqrt pada Jump Search
#include <vector> // Untuk Boyer-Moore

using namespace std;

// Struktur data HewanPasien
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

// Deklarasi head untuk Linked List
HewanPasien *head = nullptr;

// Struktur data untuk Stack
struct StackNode
{
    HewanPasien *data;
    StackNode *next;
};
StackNode *top = nullptr;

// Struktur data untuk Queue
struct QueueNode
{
    HewanPasien *data;
    QueueNode *next;
};
QueueNode *front = nullptr;
QueueNode *rear = nullptr;

// Fungsi input untuk memasukkan ID Hewan
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
            return id;
        }
    }
}

// Fungsi input untuk memasukkan umur hewan
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

// Cek apakah ID sudah ada pada linked list
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

// Fungsi untuk menambahkan data hewan pasien
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

// Fungsi untuk menampilkan semua hewan pasien
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

HewanPasien* getTail(HewanPasien* head) {
    while (head != nullptr && head->next != nullptr) {
        head = head->next;
    }
    return head;
}

HewanPasien* split(HewanPasien* head) {
    if (head == nullptr || head->next == nullptr) {
        return nullptr;
    }
    
    HewanPasien* slow = head;
    HewanPasien* fast = head->next;
    
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    HewanPasien* mid = slow->next;
    slow->next = nullptr;  
    return mid; 
}

// Fungsi merge untuk menggabungkan dua linked list yang sudah diurutkan
HewanPasien* mergeAscending(HewanPasien* left, HewanPasien* right) {
    if (!left) return right;
    if (!right) return left;
    
    // Gabungkan node sesuai urutan ID
    if (left->id < right->id) {
        left->next = mergeAscending(left->next, right);
        return left;
    } else {
        right->next = mergeAscending(left, right->next);
        return right;
    }
}

// Fungsi mergeSort untuk mengurutkan linked list secara rekursif
HewanPasien* mergeSortAscending(HewanPasien* head) {
    if (!head || !head->next) {
        return head; 
    }

    HewanPasien* mid = split(head);
    HewanPasien* left = mergeSortAscending(head);  
    HewanPasien* right = mergeSortAscending(mid); 
    
    return mergeAscending(left, right); 
}

HewanPasien* partition(HewanPasien* head, HewanPasien* end, HewanPasien** newHead, HewanPasien** newEnd) {
    HewanPasien* pivot = end;
    HewanPasien* prev = nullptr;
    HewanPasien* curr = head;
    HewanPasien* tail = pivot;

    while (curr != pivot) {
        if (curr->id > pivot->id) {  
            if (!(*newHead)) {
                *newHead = curr;
            }
            prev = curr;
            curr = curr->next;
        } else {
            if (prev) {
                prev->next = curr->next;
            }
            HewanPasien* temp = curr->next;
            curr->next = nullptr;
            tail->next = curr;
            tail = curr;
            curr = temp;
        }
    }

    if (!(*newHead)) {
        *newHead = pivot;
    }

    *newEnd = tail;
    return pivot;
}

HewanPasien* quickSortDescendingRecur(HewanPasien* head, HewanPasien* end) {
    if (!head || head == end) {
        return head;  
    }

    HewanPasien* newHead = nullptr;
    HewanPasien* newEnd = nullptr;

    HewanPasien* pivot = partition(head, end, &newHead, &newEnd);

    if (newHead != pivot) {
        HewanPasien* temp = newHead;
        while (temp->next != pivot) {
            temp = temp->next;
        }
        temp->next = nullptr;

        newHead = quickSortDescendingRecur(newHead, temp);
        temp = getTail(newHead);
        temp->next = pivot;
    }

    pivot->next = quickSortDescendingRecur(pivot->next, newEnd);
    return newHead;
}

void quickSortDescending(HewanPasien** headRef) {
    *headRef = quickSortDescendingRecur(*headRef, getTail(*headRef));
}

void sortAscending() {
    head = mergeSortAscending(head);
}

void sortDescending() {
    quickSortDescending(&head);
}

bool cekIDStack(StackNode *top, int id)
{
    StackNode *current = top;
    while (current != nullptr)
    {
        if (current->data->id == id)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

bool cekIDQueue(QueueNode *front, int id)
{
    QueueNode *current = front;
    while (current != nullptr)
    {
        if (current->data->id == id)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

// Fungsi untuk menambahkan data pasien ke Stack
void push()
{
    if (head == nullptr)
    {
        cout << "Tidak ada data hewan pasien yang tersedia.\n";
        return;
    }

    if (cekIDStack(top, head->id))
    {
        cout << "ID hewan sudah ada di Stack. Tidak bisa memasukkan data yang sama.\n";
        return;
    }

    StackNode *newNode = new StackNode();
    newNode->data = head;
    newNode->next = top;
    top = newNode;
    cout << "Pasien dengan ID " << head->id << " berhasil ditambahkan ke Stack.\n";
}

// Fungsi untuk mengambil data pasien dari Stack (pop)
void pop()
{
    if (top == nullptr)
    {
        cout << "Stack kosong, tidak ada data untuk diambil.\n";
        return;
    }

    StackNode *temp = top;
    top = top->next;
    cout << "Data pasien dengan ID " << temp->data->id << " telah diambil dari Stack.\n";
    delete temp;
}

// Fungsi untuk melihat data teratas pada Stack
void peekStack()
{
    if (top == nullptr)
    {
        cout << "Stack kosong.\n";
        return;
    }

    HewanPasien *pasien = top->data;
    cout << "Data pasien teratas di Stack:\n";
    cout << "ID Hewan: " << pasien->id << ", Nama Hewan: " << pasien->nama << "\n";
}

// Fungsi untuk menampilkan semua data pada Stack
void tampilkanStack()
{
    if (top == nullptr)
    {
        cout << "Stack kosong.\n";
        return;
    }

    StackNode *current = top;
    while (current != nullptr)
    {
        HewanPasien *pasien = current->data;
        cout << "|=================================================================|\n";
        cout << "              ID Hewan      : " << pasien->id << "\n";
        cout << "              Nama Hewan    : " << pasien->nama << "\n";
        cout << "|=================================================================|\n";
        current = current->next;
    }
}

// Fungsi untuk menambahkan data pasien ke Queue (enqueue)
void enqueue()
{
    if (head == nullptr)
    {
        cout << "Tidak ada data hewan pasien yang tersedia.\n";
        return;
    }

    if (cekIDQueue(front, head->id))
    {
        cout << "ID hewan sudah ada di Queue. Tidak bisa memasukkan data yang sama.\n";
        return;
    }

    QueueNode *newNode = new QueueNode();
    newNode->data = head;
    newNode->next = nullptr;

    if (rear == nullptr)
    {
        front = rear = newNode;
    }
    else
    {
        rear->next = newNode;
        rear = newNode;
    }

    cout << "Pasien dengan ID " << head->id << " berhasil ditambahkan ke Queue.\n";
}

// Fungsi untuk mengambil data pasien dari Queue (dequeue)
void dequeue()
{
    if (front == nullptr)
    {
        cout << "Queue kosong, tidak ada data untuk diambil.\n";
        return;
    }

    QueueNode *temp = front;
    front = front->next;

    if (front == nullptr)
    {
        rear = nullptr;
    }

    cout << "Data pasien dengan ID " << temp->data->id << " telah diambil dari Queue.\n";
    delete temp;
}

// Fungsi untuk melihat data terdepan di Queue
void peekQueue()
{
    if (front == nullptr)
    {
        cout << "Queue kosong.\n";
        return;
    }

    HewanPasien *pasien = front->data;
    cout << "Data pasien terdepan di Queue:\n";
    cout << "ID Hewan: " << pasien->id << ", Nama Hewan: " << pasien->nama << "\n";
}

// Fungsi untuk menampilkan semua data pada Queue
void tampilkanQueue()
{
    if (front == nullptr)
    {
        cout << "Queue kosong.\n";
        return;
    }

    QueueNode *current = front;
    while (current != nullptr)
    {
        HewanPasien *pasien = current->data;
        cout << "|=================================================================|\n";
        cout << "              ID Hewan      : " << pasien->id << "\n";
        cout << "              Nama Hewan    : " << pasien->nama << "\n";
        cout << "|=================================================================|\n";
        current = current->next;
    }
}

void menuStack()
{
    int pilihan;
    do
    {
        system("cls");
        cout << "==========================\n";
        cout << "|      Menu Stack        |\n";
        cout << "==========================\n";
        cout << "| 1. Push                |\n";
        cout << "| 2. Pop                 |\n";
        cout << "| 3. Peek                |\n";
        cout << "| 4. Show                |\n";
        cout << "| 5. Back                |\n";
        cout << "==========================\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            push();
            break;
        case 2:
            pop();
            break;
        case 3:
            peekStack();
            break;
        case 4:
            tampilkanStack();
            break;
        case 5:
            cout << "Kembali ke menu utama...\n";
            break;
        default:
            cout << "Pilihan tidak valid, silakan coba lagi.\n";
        }
        system("pause");
    } while (pilihan != 5);
}

void menuQueue()
{
    int pilihan;
    do
    {
        system("cls");
        cout << "==========================\n";
        cout << "|      Menu Queue        |\n";
        cout << "==========================\n";
        cout << "| 1. Enqueue             |\n";
        cout << "| 2. Dequeue             |\n";
        cout << "| 3. Peek                |\n";
        cout << "| 4. Show                |\n";
        cout << "| 5. Back                |\n";
        cout << "==========================\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;

        switch (pilihan)
        {
        case 1:
            enqueue();
            break;
        case 2:
            dequeue();
            break;
        case 3:
            peekQueue();
            break;
        case 4:
            tampilkanQueue();
            break;
        case 5:
            cout << "Kembali ke menu utama...\n";
            break;
        default:
            cout << "Pilihan tidak valid, silakan coba lagi.\n";
        }
        system("pause");
    } while (pilihan != 5);
}

// Fungsi untuk metode pencarian menggunakan Fibonacci Search
HewanPasien* fibonacciSearch(int x) {
    if (head == nullptr) {
        cout << "Daftar pasien kosong. Tidak ada yang bisa dicari.\n";
        return nullptr;
    }

    int size = 0;
    HewanPasien* current = head;
    while (current != nullptr) {
        size++;
        current = current->next;
    }

    int fibMMm2 = 0;   
    int fibMMm1 = 1;   
    int fibM = fibMMm2 + fibMMm1; 

    while (fibM < size) {
        fibMMm2 = fibMMm1;
        fibMMm1 = fibM;
        fibM = fibMMm2 + fibMMm1;
    }

    int offset = -1;
    current = head;
    
    while (fibM > 1) {
        int i = min(offset + fibMMm2, size - 1);

        HewanPasien* temp = head;
        for (int j = 0; j < i && temp != nullptr; j++)  {
                temp = temp->next;
            }  
        
        if (temp == nullptr) break;

        if (temp->id < x) {
            fibM = fibMMm1;
            fibMMm1 = fibMMm2;
            fibMMm2 = fibM - fibMMm1;
            offset = i;

        } else if (temp->id > x) {
            fibM = fibMMm2;
            fibMMm1 = fibMMm1 - fibMMm2;
            fibMMm2 = fibM - fibMMm1;

        } else {
            return temp;
        }
    }

     if (offset == -1) {
        if (head->id == x) {
            return head;
        }
    }
    
    if (fibMMm1 && offset + 1 < size) {
        HewanPasien* temp = head;
        for (int j  = 0; j <= offset + 1; j++) {
            temp = temp->next;
        }
         if (temp != nullptr && temp->id == x) {
            return temp;
        }
    }
    return nullptr; 
}

HewanPasien* jumpSearch(int x) {
    if (head == nullptr) {
        return nullptr; 
    }

    int step = sqrt(10); 
    HewanPasien *prev = head;
    HewanPasien *current = head;

    while (current->next != nullptr && current->id < x) {
        prev = current;
        for (int i = 0; i < step && current->next != nullptr; i++) {
            current = current->next;
        }
    }

    while (prev != nullptr && prev->id < x) {
        prev = prev->next;
    }

    if (prev != nullptr && prev->id == x) {
        return prev; 
    }

    return nullptr; 
}


void buildBadCharTable(const string &pattern, vector<int> &badCharTable) {
    int m = pattern.length();
    badCharTable.assign(256, -1);
    for (int i = 0; i < m; i++) {
        badCharTable[(int)pattern[i]] = i;
    }
}

// Fungsi pencarian Boyer-Moore
HewanPasien* boyerMooreSearch(const string &pattern) {
    HewanPasien *current = head;
    vector<int> badCharTable;
    buildBadCharTable(pattern, badCharTable);

    while (current != nullptr) {
        string text = current->nama;
        int n = text.size();
        int m = pattern.size();
        int shift = 0;

        while (shift <= (n - m)) {
            int j = m - 1;

            while (j >= 0 && pattern[j] == text[shift + j]) {
                j--;
            }

            if (j < 0) {
                return current;
            } else {
                shift += max(1, j - badCharTable[(int)text[shift + j]]);
            }
        }
        current = current->next;
    }

    return nullptr;
}

// Menu untuk memilih metode pencarian
void menuPencarian() {
    int pilihan;
    int id;
    string nama;
    HewanPasien *hasil = nullptr;

    do {
        system("cls");
        cout << "==========================\n";
        cout << "|    Menu Pencarian      |\n";
        cout << "==========================\n";
        cout << "| 1. Fibonacci Search    |\n";
        cout << "| 2. Jump Search         |\n";
        cout << "| 3. Boyer-Moore Search  |\n";
        cout << "| 4. Kembali             |\n";
        cout << "==========================\n";
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
        case 1:
            cout << "Masukkan ID yang dicari: ";
            cin >> id;
            hasil = fibonacciSearch(id);
            if (head == nullptr) {
              cout << "Daftar hewan pasien kosong, tidak ada data yang bisa dicari.\n";
                break;
            }
            if (hasil != nullptr) {
                cout << "Hewan dengan ID " << id << " ditemukan: " << hasil->nama << "\n";
            } else {
                cout << "Hewan dengan ID " << id << " tidak ditemukan.\n";
            }
            break;
        case 2:
            cout << "Masukkan ID yang dicari: ";
            cin >> id;
            sortAscending();  
            hasil = jumpSearch(id);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      
            if (hasil != nullptr) {
                cout << "Hewan dengan ID " << id << " ditemukan: " << hasil->nama << "\n";
            } else {
                cout << "Hewan dengan ID " << id << " tidak ditemukan.\n";
            }
            break;
        case 3:
            cout << "Masukkan nama yang dicari: ";
            getline(cin, nama);
            hasil = boyerMooreSearch(nama);
            if (hasil != nullptr) {
                cout << "Hewan dengan nama " << nama << " ditemukan: ID = " << hasil->id << "\n";
            } else {
                cout << "Hewan dengan nama " << nama << " tidak ditemukan.\n";
            }
            break;
        case 4:
            cout << "Kembali ke menu utama...\n";
            break;
        default:
            cout << "Pilihan tidak valid, silakan coba lagi.\n";
        }

        system("pause");
    } while (pilihan != 4);
}

// Menu utama program
int main() {
    int pilihan;
    do {
        system("cls");
        cout << "=====================================\n";
        cout << "| Selamat Datang di Klinik Hewan KH |\n";
        cout << "|           Anabul Care             |\n";
        cout << "=====================================\n";
        cout << "|  1. Tambah Hewan Pasien           |\n";
        cout << "|  2. Tampilkan Semua Pasien        |\n";
        cout << "|  3. Menu Stack                    |\n";
        cout << "|  4. Menu Queue                    |\n";
        cout << "|  5. Urutkan Ascending             |\n";
        cout << "|  6. Urutkan Descending            |\n";
        cout << "|  7. Menu Pencarian                |\n";
        cout << "|  8. Keluar                        |\n";
        cout << "=====================================\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
        case 1:
            tambahHewan();
            break;
        case 2:
            tampilkanSemuaHewan();
            break;
        case 3:
            menuStack();
            break;
        case 4:
            menuQueue();
            break;
        case 5:
            sortAscending();
            tampilkanSemuaHewan();
            break;
        case 6:
            sortDescending();
            tampilkanSemuaHewan();
            break;
        case 7:
            menuPencarian();
            break;
        case 8:
            cout << "Keluar dari program.\n";
            break;
        default:
            cout << "Pilihan tidak valid!\n";
        }

        if (pilihan != 8) {
            cout << "Tekan Enter untuk melanjutkan...";
            cin.get();
        }

    } while (pilihan != 8);

    return 0;
}