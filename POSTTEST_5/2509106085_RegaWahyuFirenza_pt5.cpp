#include <iostream>
#include <string>
using namespace std;

// struktur node untuk circular linked list perpustakaan
struct BukuNode {
    string judulBuku;
    BukuNode* next;

    // ini constructor nya
    BukuNode(string judul) {
        judulBuku = judul;
        next = nullptr;
    }
};

// fungsi insert di akhir circular linked list untuk membangun data
BukuNode* tambahBuku(BukuNode* head, string judul) {
    BukuNode* newNode = new BukuNode(judul);
    if (head == nullptr) {
        newNode->next = newNode;
        return newNode;
    }
    
    BukuNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

/**
 * fungsi untuk mencari buku berdasarkan judulnya
 */
bool cariBuku(BukuNode* head, string judulDicari) {
    // --- LENGKAPI KODENYA DI SINI BANG---

    // pertama, mastiin dulu listnya nda kosong.kalau kosong ya jelas bukunya nda ada.
    if (head == nullptr) {
        return false;
    }

    // kita mulai penelusuran dari buku paling pertama (head)
    BukuNode* temp = head;

    // kita pakai perulangan do-while supaya program ngecek dulu baru pindah, 
    // karena kalau pakai while biasa dia bakal langsung berhenti di awal (karena temp = head)
    do {
        // cek kalau judul buku yang dipegang sekarang sama dengan yang dicari
        if (temp->judulBuku == judulDicari) {
            return true; // kalau cocok, langsung balikin true (ketemu)
        }
        
        // kalau belum cocok,kita geser ke buku berikutnya
        temp = temp->next;

    } while (temp != head); // pokoknya muter terus sampai kita balik lagi ke titik awal (head)

    // kalau sudah keliling satu putaran dan nda ketemu juga, berarti bukunya emang nda ada
    return false;

    // -----------------------------
}

int main() {
    BukuNode* head = nullptr;
    
    head = tambahBuku(head, "Struktur Data dengan C++");
    head = tambahBuku(head, "Pengantar Algoritma");
    head = tambahBuku(head, "Pemrograman Berorientasi Objek");
    head = tambahBuku(head, "Sistem Basis Data");

    string buku1 = "Pengantar Algoritma";
    string buku2 = "Kalkulus Lanjut";

    cout << "Mencari buku '" << buku1 << "': " 
         << (cariBuku(head, buku1) ? "Ditemukan" : "Tidak Ditemukan") << endl; 

    cout << "Mencari buku '" << buku2 << "': " 
         << (cariBuku(head, buku2) ? "Ditemukan" : "Tidak Ditemukan") << endl; 

    return 0;
}