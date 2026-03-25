#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

#define ALFABET 256

struct Hewan {
    int id;
    string nama, jenis;
    int harga;
};

void swapData(Hewan *a, Hewan *b) {
    Hewan temp = *a;
    *a = *b;
    *b = temp;
}

void lihatData(Hewan *ptr, int n) {
    if (n == 0) {
        cout << "\n[!] Waduh, datanya masih kosong nih.\n";
        return;
    }
    cout << "\n============================================================" << endl;
    cout << " No | ID   | Nama Hewan          | Jenis      | Harga       " << endl;
    cout << "------------------------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        printf(" %-2d | %-4d | %-19s | %-10s | Rp%-10d \n", 
                i + 1, (ptr + i)->id, (ptr + i)->nama.c_str(), 
                (ptr + i)->jenis.c_str(), (ptr + i)->harga);
    }
    cout << "============================================================" << endl;
}

int fibonacciSearch(Hewan *arr, int n, int target) {
    int fib2 = 0;
    int fib1 = 1;
    int fib = fib1 + fib2;

    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib1 + fib2;
    }

    int offset = -1; 
    while (fib > 1) {
        int i = offset + fib2;
        if (i >= n) i = n - 1; 

        if (arr[i].id == target) return i;
        else if (arr[i].id < target) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i; 
        } else {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        }
    }
    if (fib1 == 1 && arr[offset + 1].id == target) return offset + 1;
    return -1;
}

void buatTabelBadChar(string &pattern, int m, int tabel[]) {
    for (int i = 0; i < ALFABET; i++) tabel[i] = -1; 
    for (int i = 0; i < m; i++) tabel[(int)pattern[i]] = i; 
}

void boyerMoore(Hewan *arr, int n_data, string pattern) {
    int m = (int)pattern.size();
    int badChar[ALFABET];
    buatTabelBadChar(pattern, m, badChar); 
    
    bool foundOverall = false;
    cout << "\n--- Hasil Pencarian Boyer-Moore ---" << endl;

    for (int idx = 0; idx < n_data; idx++) {
        string text = arr[idx].nama;
        int n = (int)text.size();
        int s = 0; 

        while (s <= n - m) {
            int j = m - 1; 
            while (j >= 0 && pattern[j] == text[s + j]) j--;

            if (j < 0) {
                cout << "[+] Kecocokan ditemukan pada: '" << text << "' (ID: " << arr[idx].id << ")" << endl;
                foundOverall = true;
                if (s + m < n) s += m - badChar[(int)text[s + m]];
                else s++;
            } else {
                int geser = j - badChar[(int)text[s + j]]; 
                if (geser < 1) geser = 1;
                s += geser;
            }
        }
    }
    if (!foundOverall) cout << "[-] Pola nama tidak ditemukan." << endl;
}

void linearSearch(Hewan *arr, int n, string target) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (arr[i].nama == target) {
            cout << "\n[+] Ketemu! '" << target << "' ada di index ke-" << i << endl;
            found = true;
            break;
        }
    }
    if (!found) cout << "\n[-] Nama tidak ditemukan.\n";
}

void bubbleSort(Hewan *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].nama > arr[j + 1].nama) swapData(&arr[j], &arr[j + 1]);
        }
    }
    cout << "\n[*] Data diurutkan berdasarkan Nama (Bubble Sort).\n";
}

void selectionSort(Hewan *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].harga < arr[min_idx].harga) min_idx = j;
        }
        swapData(&arr[min_idx], &arr[i]);
    }
    cout << "\n[*] Data diurutkan berdasarkan Harga (Selection Sort).\n";
}

int partition(Hewan *arr, int low, int high) {
    int pivot = arr[high].id;
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].id < pivot) {
            i++;
            swapData(&arr[i], &arr[j]);
        }
    }
    swapData(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(Hewan *arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void inputData(Hewan *arr, int *n) {
    cout << "\n>>> Tambah Data Hewan Baru <<<" << endl;
    cout << "ID (Angka)  : "; cin >> arr[*n].id;
    cin.ignore();
    cout << "Nama Hewan  : "; getline(cin, arr[*n].nama);
    cout << "Jenis Hewan : "; getline(cin, arr[*n].jenis);
    cout << "Harga       : "; cin >> arr[*n].harga;
    (*n)++;
    cout << ">> Data berhasil disimpan.\n";
}

int main() {
    Hewan dataPet[100]; 
    int jml = 0;
    int pil;

    do {
        cout << "\n=== MENU PAWCARE PETSHOP ===" << endl;
        cout << "1. Tambah Data" << endl;
        cout << "2. Tampil Semua Data (Pointer)" << endl;
        cout << "3. Cari Nama (Linear Search)" << endl;
        cout << "4. Cari ID (Fibonacci Search - Urutkan ID Dulu!)" << endl;
        cout << "5. Cari Pola Nama (Boyer-Moore Search)" << endl;
        cout << "6. Urut Nama (Bubble Sort)" << endl;
        cout << "7. Urut Harga (Selection Sort)" << endl;
        cout << "8. Urut ID (Quick Sort)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu: "; cin >> pil;

        if (pil == 1) {
            inputData(dataPet, &jml);
        } else if (pil == 2) {
            lihatData(dataPet, jml);
        } else if (pil == 3) {
            string n; cout << "Cari Nama: "; cin.ignore(); getline(cin, n);
            linearSearch(dataPet, jml, n);
        } else if (pil == 4) {
            int target; cout << "Cari ID: "; cin >> target;
            int res = fibonacciSearch(dataPet, jml, target);
            if (res != -1) cout << "Ditemukan di indeks " << res << endl;
            else cout << "ID tidak ditemukan." << endl;
        } else if (pil == 5) {
            string p; cout << "Masukkan pola nama: "; cin.ignore(); getline(cin, p);
            boyerMoore(dataPet, jml, p);
        } else if (pil == 6) {
            bubbleSort(dataPet, jml);
        } else if (pil == 7) {
            selectionSort(dataPet, jml);
        } else if (pil == 8) {
            quickSort(dataPet, 0, jml - 1);
            cout << "\n[*] Data diurutkan berdasarkan ID (Quick Sort).\n";
        }

    } while (pil != 0);

    return 0;
}