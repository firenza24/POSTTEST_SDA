#include <iostream>
#include <string>

#define MAX 100

using namespace std;

struct Hewan {
    int id;
    string nama, jenis;
    int harga;
};

Hewan queueAntrean[MAX];
int front = -1, rear = -1;

Hewan stackRiwayat[MAX];
int top = -1;

bool isQueueFull() {
    return rear == MAX - 1;
}

bool isQueueEmpty() {
    return front == -1 || front > rear;
}

void enqueue(Hewan h) {
    if (isQueueFull()) {
        cout << "\n[!] Antrean penuh (Overflow)!" << endl;
        return;
    }
    if (front == -1) front = 0;
    rear++;
    *(queueAntrean + rear) = h; 
    cout << "\n[+] " << h.nama << " berhasil masuk antrean." << endl;
}

Hewan dequeue() {
    if (isQueueEmpty()) {
        cout << "\n[!] Antrean kosong (Underflow)!" << endl;
        return {0, "", "", 0};
    }
    Hewan h = *(queueAntrean + front);
    front++;
    if (isQueueEmpty()) {
        front = rear = -1;
    }
    return h;
}

bool isStackFull() {
    return top >= MAX - 1;
}

bool isStackEmpty() {
    return top < 0;
}

void push(Hewan h) {
    if (isStackFull()) {
        cout << "\n[!] Riwayat penuh (Overflow)!" << endl;
        return;
    }
    top++;
    *(stackRiwayat + top) = h;
}

void pop() {
    if (isStackEmpty()) {
        cout << "\n[!] Riwayat kosong (Underflow)!" << endl;
        return;
    }
    cout << "\n[-] Riwayat terakhir: " << (*(stackRiwayat + top)).nama << " dihapus." << endl;
    top--;
}

void tampilSatuHewan(Hewan *h) {
    cout << "ID: " << h->id << " | Nama: " << h->nama << " | Jenis: " << h->jenis << endl;
}

void tampilAntrean() {
    if (isQueueEmpty()) {
        cout << "\n[!] Nggak ada antrean pasien." << endl;
        return;
    }
    cout << "\n--- DAFTAR ANTREAN (FRONT KE REAR) ---" << endl;
    for (Hewan *ptr = (queueAntrean + front); ptr <= (queueAntrean + rear); ptr++) {
        cout << ">> ";
        tampilSatuHewan(ptr);
    }
}

void tampilRiwayat() {
    if (isStackEmpty()) {
        cout << "\n[!] Belum ada riwayat tindakan." << endl;
        return;
    }
    cout << "\n--- RIWAYAT TINDAKAN (TOP KE BOTTOM) ---" << endl;
    for (Hewan *ptr = (stackRiwayat + top); ptr >= stackRiwayat; ptr--) {
        cout << "<< ";
        tampilSatuHewan(ptr);
    }
}

int main() {
    Hewan dataPet[MAX];
    int jml = 0, pil;

    do {
        cout << "\n=== MENU PAWCARE PETSHOP ===" << endl;
        cout << "1. Registrasi Hewan Baru" << endl;
        cout << "2. Masukkan ke Antrean (Enqueue)" << endl;
        cout << "3. Panggil Pasien (Dequeue & Push ke Riwayat)" << endl;
        cout << "4. Hapus Riwayat Terakhir (Pop)" << endl;
        cout << "5. Intip (Peek Antrean & Riwayat)" << endl;
        cout << "6. Lihat Semua Antrean" << endl;
        cout << "7. Lihat Semua Riwayat" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih menu: "; cin >> pil;

        if (pil == 1) {
            if (jml < MAX) {
                cout << "\n--- Registrasi ---" << endl;
                cout << "ID: "; cin >> dataPet[jml].id;
                cin.ignore();
                cout << "Nama: "; getline(cin, dataPet[jml].nama);
                cout << "Jenis: "; getline(cin, dataPet[jml].jenis);
                cout << "Harga: "; cin >> dataPet[jml].harga;
                jml++;
                cout << "[*] Data tersimpan di registrasi." << endl;
            } else {
                cout << "\n[!] Kapasitas database penuh!" << endl;
            }
        }
        else if (pil == 2) {
            if (jml == 0) cout << "\n[!] Daftar hewan masih kosong! Registrasi dulu." << endl;
            else {
                int idx;
                cout << "Pilih nomor urut data (1-" << jml << "): "; cin >> idx;
                if (idx > 0 && idx <= jml) {
                    enqueue(dataPet[idx-1]);
                } else {
                    cout << "[!] Index data nggak valid." << endl;
                }
            }
        }
        else if (pil == 3) {
            if (!isQueueEmpty()) {
                Hewan h = dequeue();
                cout << "\n[!] MEMANGGIL: " << h.nama << " (ID: " << h.id << ") ke ruang dokter." << endl;
                push(h);
            } else {
                cout << "\n[!] Antrean kosong! Tidak ada yang bisa dipanggil." << endl;
            }
        }
        else if (pil == 4) {
            pop();
        }
        else if (pil == 5) {
            cout << "\n--- PEEK DATA ---" << endl;
            if (!isQueueEmpty()) {
                cout << "Pasien terdepan (Antrean): " << (*(queueAntrean + front)).nama << endl;
            } else {
                cout << "Antrean: (Kosong)" << endl;
            }

            if (!isStackEmpty()) {
                cout << "Tindakan terakhir (Riwayat): " << (*(stackRiwayat + top)).nama << endl;
            } else {
                cout << "Riwayat: (Kosong)" << endl;
            }
        }
        else if (pil == 6) {
            tampilAntrean();
        }
        else if (pil == 7) {
            tampilRiwayat();
        }
        else if (pil == 0) {
            cout << "\nTerima kasih! Program Pawcare selesai." << endl;
        }
        else {
            cout << "\n[!] Pilihan tidak ada di menu. Coba lagi." << endl;
        }

    } while (pil != 0);

    return 0;
}