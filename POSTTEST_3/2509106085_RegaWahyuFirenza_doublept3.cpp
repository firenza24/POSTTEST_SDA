#include <iostream>
#include <string>

#define MAX 100 

using namespace std;

struct Kereta {
    string nomor;
    string nama;
    string asal;
    string tujuan;
    int harga;
};

struct Tiket {
    string namaPenumpang;
    Kereta dataKereta;
};

Tiket antrian[MAX];
int front = -1, rear = -1;

Tiket riwayat[MAX]; 
int topRiwayat = -1;

Tiket redoStack[MAX]; 
int topRedo = -1;

void tampilSatuTiket(Tiket *t) {
    cout << "Penumpang: " << t->namaPenumpang 
         << " | KA: " << t->dataKereta.nama 
         << " (" << t->dataKereta.asal << " -> " << t->dataKereta.tujuan << ")" << endl;
}

bool isQueueEmpty() { return front == -1 || front > rear; }
bool isQueueFull() { return rear == MAX - 1; }

void enqueue(Tiket data) {
    if (isQueueFull()) {
        cout << "Queue overflow" << endl;
        return;
    }
    if (front == -1) front = 0;
    rear++;
    antrian[rear] = data;
}

Tiket dequeue() {
    Tiket data = antrian[front];
    front++;
    if (isQueueEmpty()) front = rear = -1;
    return data;
}

bool isStackEmpty(int top) { return top < 0; }
bool isStackFull(int top) { return top >= MAX - 1; }

void push(Tiket stack[], int &top, Tiket data) {
    if (isStackFull(top)) return;
    stack[++top] = data;
}

Tiket pop(Tiket stack[], int &top) {
    return stack[top--];
}

void undoTransaksi() {
    if (isStackEmpty(topRiwayat)) {
        cout << "Undo Gagal: Tidak ada transaksi untuk dibatalkan." << endl;
        return;
    }
    Tiket data = pop(riwayat, topRiwayat);
    push(redoStack, topRedo, data);
    enqueue(data); 
    cout << "Undo Berhasil: Transaksi " << data.namaPenumpang << " dikembalikan ke antrian." << endl;
}

void redoTransaksi() {
    if (isStackEmpty(topRedo)) {
        cout << "Redo Gagal: Tidak ada aksi undo sebelumnya." << endl;
        return;
    }
    Tiket data = pop(redoStack, topRedo);
    push(riwayat, topRiwayat, data);
    cout << "Redo Berhasil: Transaksi " << data.namaPenumpang << " dipulihkan ke riwayat." << endl;
}

void tampilJadwal(Kereta* arr, int n) {
    cout << "\n=== JADWAL KERETA ===\n";
    for (int i = 0; i < n; i++) {
        cout << i + 1 << ". " << arr[i].nama << " (" << arr[i].asal << " -> " << arr[i].tujuan << ") | Rp" << arr[i].harga << endl;
    }
}

int main() {
    Kereta jadwal[3] = {
        {"101", "A", "Berau", "Surabaya", 500000},
        {"105", "B", "Samarinda", "Jakarta", 600000},
        {"102", "C", "Balikpapan", "Bandung", 74000}
    };
    int pilih;

    do {
        cout << "\n--- SISTEM TIKET (STACK & QUEUE) ---" << endl;
        cout << "1. Antri Beli Tiket (Enqueue)" << endl;
        cout << "2. Proses Tiket Terdepan (Dequeue & Push Riwayat)" << endl;
        cout << "3. Undo Transaksi (Batalkan Transaksi Terakhir)" << endl;
        cout << "4. Redo Transaksi (Kembalikan Pembatalan)" << endl;
        cout << "5. Lihat Semua Data (Antrian & Riwayat)" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilih: "; cin >> pilih;

        if (pilih == 1) {
            string namaP;
            int no;
            tampilJadwal(jadwal, 3);
            cout << "Masukkan Nama Penumpang: "; cin.ignore(); getline(cin, namaP);
            cout << "Pilih Nomor Kereta: "; cin >> no;
            
            if (no >= 1 && no <= 3) {
                Tiket t = {namaP, jadwal[no-1]};
                enqueue(t);
                cout << "Penumpang " << namaP << " berhasil masuk antrian." << endl;
            } else {
                cout << "Pilihan tidak valid!" << endl;
            }
        } 
        else if (pilih == 2) {
            if (!isQueueEmpty()) {
                Tiket p = dequeue();
                push(riwayat, topRiwayat, p);
                topRedo = -1; 
                cout << "Memproses: "; tampilSatuTiket(&p);
            } else {
                cout << "Antrian Kosong." << endl;
            }
        } 
        else if (pilih == 3) undoTransaksi();
        else if (pilih == 4) redoTransaksi();
        else if (pilih == 5) {
            cout << "\n--- ANTRIAN SAAT INI (FIFO) ---" << endl;
            if(isQueueEmpty()) cout << "Kosong" << endl;
            for(int i = front; i <= rear && i != -1; i++) {
                cout << i - front + 1 << ". "; tampilSatuTiket(&antrian[i]);
            }

            cout << "\n--- RIWAYAT TRANSAKSI (LIFO) ---" << endl;
            if(isStackEmpty(topRiwayat)) cout << "Kosong" << endl;
            for(int i = topRiwayat; i >= 0; i--) {
                cout << "[" << i + 1 << "] "; tampilSatuTiket(&riwayat[i]);
            }
        }
        else if (pilih == 0) {
            cout << "Keluar dari program." << endl;
        }
        else {
            cout << "Pilihan menu tidak ada!" << endl;
        }
    } while (pilih != 0);

    return 0;
}