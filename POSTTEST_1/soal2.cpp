#include <iostream>
#include <string>

using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    cout << "   >>> MENCARI IPK TERTINGGI <<<   " << endl;
    cout << "-----------------------------------" << endl;

    Mahasiswa daftarMhs[5];
    int i = 0;

    while (i < 5) {
        cout << "[ Mahasiswa Ke-" << i + 1 << " ]" << endl;
        
        cout << "Nama Lengkap : ";
        getline(cin >> ws, daftarMhs[i].nama);
        
        cout << "NIM  : ";
        cin >> daftarMhs[i].nim;
        
        cout << "IPK     : ";
        cin >> daftarMhs[i].ipk;
        
        cout << endl;
        i++;
    }

    int idxBest = 0; 
    for (int j = 1; j < 5; j++) {
        if (daftarMhs[j].ipk > daftarMhs[idxBest].ipk) {
            idxBest = j;
        }
    }

    cout << "=======================================" << endl;
    cout << "     HASIL PENCARIAN IPK TERTINGGI" << endl;
    cout << "=======================================" << endl;
    cout << "Nama Mahasiswa : " << daftarMhs[idxBest].nama << endl;
    cout << "NIM            : " << daftarMhs[idxBest].nim << endl;
    cout << "IPK            : " << daftarMhs[idxBest].ipk << endl;
    cout << "=======================================" << endl;

    return 0;
}