#include <iostream>
#include <string>

using namespace std;

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

void searchNama(Hewan *ptr, int n, string target) {
    bool found = false;
    for (int i = 0; i < n; i++) {
        if ((ptr + i)->nama == target) { 
            cout << "\n[+] Mantap! '" << target << "' ketemu di index ke-" << i << endl;
            printf(" Detail -> ID: %d | Jenis: %s | Harga: Rp%d\n", 
                    (ptr+i)->id, (ptr+i)->jenis.c_str(), (ptr+i)->harga);
            found = true;
            break;
        }
    }
    if (!found) cout << "\n[-] Hmm, nama hewan itu nggak ada di list.\n";
}

int fibSearch(Hewan *arr, int n, int x) {
    int f2 = 0; 
    int f1 = 1; 
    int fM = f2 + f1; 

    while (fM < n) {
        f2 = f1;
        f1 = fM;
        fM = f2 + f1;
    }

    int offset = -1;
    int iterasi = 1;

    cout << "\n>>> Cek Proses Fibonacci <<<" << endl;
    while (fM > 1) {
        int i = ((offset + f2) <= (n - 1)) ? (offset + f2) : (n - 1);
        
        cout << "Iterasi " << iterasi++ << ": Cek Index [" << i << "] ID: " << arr[i].id << endl;

        if (arr[i].id < x) {
            fM = f1;
            f1 = f2;
            f2 = fM - f1;
            offset = i;
        } else if (arr[i].id > x) {
            fM = f2;
            f1 = f1 - f2;
            f2 = fM - f1;
        } else {
            return i;
        }
    }

    if (f1 && arr[offset + 1].id == x) return offset + 1;

    return -1;
}

void bubbleSort(Hewan *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].nama > arr[j + 1].nama) {
                swapData(&arr[j], &arr[j + 1]); 
            }
        }
    }
    cout << "\n[*] Oke, data udah urut berdasarkan Nama.\n";
}

void selectionSort(Hewan *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].harga < arr[min_idx].harga) {
                min_idx = j;
            }
        }
        swapData(&arr[min_idx], &arr[i]);
    }
    cout << "\n[*] Sip, data udah urut dari yang paling Murah.\n";
}

void inputData(Hewan *arr, int *n) {
    cout << "\n--- Tambah Data Baru ---" << endl;
    cout << "ID (Angka)  : "; cin >> arr[*n].id;
    cin.ignore();
    cout << "Nama Hewan  : "; getline(cin, arr[*n].nama);
    cout << "Jenis Hewan : "; getline(cin, arr[*n].jenis);
    cout << "Harga       : "; cin >> arr[*n].harga;
    (*n)++;
    cout << ">> Sip, data udah masuk.\n";
}

int main() {
    Hewan dataPet[100]; 
    int jml = 0;
    int pil;

    do {
        cout << "\n=== MENU PAWCARE PETSHOP ===" << endl;
        cout << "1. Tambah Data" << endl;
        cout << "2. Tampil Data" << endl;
        cout << "3. Cari Nama (Linear)" << endl;
        cout << "4. Cari ID (Fibonacci)" << endl;
        cout << "5. Urut Nama (Bubble)" << endl;
        cout << "6. Urut Harga (Selection)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu: "; cin >> pil;

        if (pil == 1) {
            inputData(dataPet, &jml);
        } else if (pil == 2) {
            lihatData(dataPet, jml);
        } else if (pil == 3) {
            string n;
            cout << "Mau cari nama apa? "; cin.ignore(); getline(cin, n);
            searchNama(dataPet, jml, n);
        } else if (pil == 4) {
            int id;
            cout << "Masukan ID yang dicari: "; cin >> id;
            int res = fibSearch(dataPet, jml, id);
            if (res != -1) cout << "\nKetemu! Ada di index: " << res << endl;
            else cout << "\nYah, ID-nya nggak ada.\n";
        } else if (pil == 5) {
            bubbleSort(dataPet, jml);
        } else if (pil == 6) {
            selectionSort(dataPet, jml);
        }

    } while (pil != 0);

    return 0;
}