#include <iostream>
#include <string>

#define MAX 100

using namespace std;

struct Hewan {
    int id;
    string nama, jenis;
    int harga;
};

struct Node {
    Hewan data;
    Node *next;
};

Node *queueFront = nullptr;
Node *queueRear = nullptr;
Node *stackTop = nullptr;

bool isQueueEmpty() {
    return queueFront == nullptr;
}

bool isStackEmpty() {
    return stackTop == nullptr;
}

void enqueue(Hewan h) {
    Node *newNode = new Node;
    newNode->data = h;
    newNode->next = nullptr;
    
    if (isQueueEmpty()) {
        queueFront = queueRear = newNode;
    } else {
        queueRear->next = newNode;
        queueRear = newNode;
    }
    cout << "\n[+] " << h.nama << " berhasil masuk antrean." << endl;
}

Hewan dequeue() {
    if (isQueueEmpty()) {
        cout << "\n[!] Antrean kosong (Underflow)!" << endl;
        return {0, "", "", 0};
    }
    
    Node *temp = queueFront;
    Hewan dataAmbil = temp->data;
    queueFront = queueFront->next;
    
    if (queueFront == nullptr) {
        queueRear = nullptr;
    }
    
    delete temp;
    return dataAmbil;
}

void push(Hewan h) {
    Node *newNode = new Node;
    newNode->data = h;
    newNode->next = stackTop;
    stackTop = newNode;
}

void pop() {
    if (isStackEmpty()) {
        cout << "\n[!] Riwayat kosong (Underflow)!" << endl;
        return;
    }
    
    Node *temp = stackTop;
    cout << "\n[-] Riwayat terakhir: " << temp->data.nama << " dihapus." << endl;
    stackTop = stackTop->next;
    delete temp;
}

void peek() {
    cout << "\n--- PEEK DATA ---" << endl;
    if (!isQueueEmpty()) {
        cout << "Pasien terdepan (Antrean): " << queueFront->data.nama << endl;
    } else {
        cout << "Antrean: (Kosong)" << endl;
    }

    if (!isStackEmpty()) {
        cout << "Tindakan terakhir (Riwayat): " << stackTop->data.nama << endl;
    } else {
        cout << "Riwayat: (Kosong)" << endl;
    }
}

void tampilSatuHewan(Hewan *h) {
    cout << "ID: " << h->id << " | Nama: " << h->nama << " | Jenis: " << h->jenis << " | Harga: " << h->harga << endl;
}

void tampilAntrean() {
    if (isQueueEmpty()) {
        cout << "\n[!] Nggak ada antrean pasien." << endl;
        return;
    }
    cout << "\n--- DAFTAR ANTREAN (FRONT KE REAR) ---" << endl;
    Node *temp = queueFront;
    while (temp != nullptr) {
        cout << ">> ";
        tampilSatuHewan(&temp->data);
        temp = temp->next;
    }
}

void tampilRiwayat() {
    if (isStackEmpty()) {
        cout << "\n[!] Belum ada riwayat tindakan." << endl;
        return;
    }
    cout << "\n--- RIWAYAT TINDAKAN (TOP KE BOTTOM) ---" << endl;
    Node *temp = stackTop;
    while (temp != nullptr) {
        cout << "<< ";
        tampilSatuHewan(&temp->data);
        temp = temp->next;
    }
}

int main() {
    Hewan databaseReg[MAX];
    int jmlReg = 0, pil;

    do {
        cout << "\n=== MENU PAWCARE PETSHOP ===" << endl;
        cout << "1. Registrasi Hewan Baru" << endl;
        cout << "2. Masukkan ke Antrean (Enqueue)" << endl;
        cout << "3. Panggil Pasien (Dequeue & Push ke Riwayat)" << endl;
        cout << "4. Hapus Riwayat Terakhir (Pop)" << endl;
        cout << "5. Intip (Peek)" << endl;
        cout << "6. Tampil Antrean" << endl;
        cout << "7. Tampil Riwayat" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu: "; cin >> pil;

        if (pil == 1) {
            if (jmlReg < MAX) {
                cout << "\n--- Registrasi ---" << endl;
                cout << "ID: "; cin >> databaseReg[jmlReg].id;
                cin.ignore();
                cout << "Nama: "; getline(cin, databaseReg[jmlReg].nama);
                cout << "Jenis: "; getline(cin, databaseReg[jmlReg].jenis);
                cout << "Harga: "; cin >> databaseReg[jmlReg].harga;
                jmlReg++;
                cout << "[*] Data tersimpan." << endl;
            } else {
                cout << "\n[!] Database registrasi penuh!" << endl;
            }
        }
        else if (pil == 2) {
            if (jmlReg == 0) cout << "\n[!] Database kosong!" << endl;
            else {
                int idx;
                cout << "Pilih nomor urut (1-" << jmlReg << "): "; cin >> idx;
                if (idx > 0 && idx <= jmlReg) {
                    enqueue(databaseReg[idx-1]);
                } else {
                    cout << "[!] Index tidak valid." << endl;
                }
            }
        }
        else if (pil == 3) {
            if (!isQueueEmpty()) {
                Hewan h = dequeue();
                cout << "\n[!] MEMANGGIL: " << h.nama << endl;
                push(h);
            } else {
                cout << "\n[!] Antrean kosong!" << endl;
            }
        }
        else if (pil == 4) {
            pop();
        }
        else if (pil == 5) {
            peek();
        }
        else if (pil == 6) {
            tampilAntrean();
        }
        else if (pil == 7) {
            tampilRiwayat();
        }
        else if (pil == 0) {
            cout << "\nTerima kasih!" << endl;
        }
        // Tambahan logika jika pilihan tidak ada di menu
        else {
            cout << "\n[!] Pilihan tidak ada dimenu! Silakan coba lagi." << endl;
        }
    } while (pil != 0);

    return 0;
}