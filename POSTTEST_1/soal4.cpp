#include <iostream>
using namespace std;

void tukarNilai(int *ptr1, int *ptr2) {
    int simpan = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = simpan;
}

int main() {
    int angkaA, angkaB;

    cout << ">>> PROGRAM PENUKARAN NILAI <<<" << endl;
    cout << "Masukkan Angka Pertama: ";
    cin >> angkaA;
    cout << "Masukkan Angka Kedua  : ";
    cin >> angkaB;

    cout << "\nKondisi Awal:" << endl;
    cout << "Angka A = " << angkaA << " | Angka B = " << angkaB << endl;

    tukarNilai(&angkaA, &angkaB);

    cout << "\nKondisi Setelah Ditukar:" << endl;
    cout << "Angka A = " << angkaA << " | Angka B = " << angkaB << endl;

    return 0;
}