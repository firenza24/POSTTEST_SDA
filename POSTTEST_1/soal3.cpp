#include <iostream>

using namespace std;

void reverseArray(int* ptr, int n) {
    int* awal = ptr;             
    int* akhir = ptr + (n - 1);  
    
    while (awal < akhir) {
        int temp = *awal;
        *awal = *akhir;
        *akhir = temp;
        
        awal++; 
        akhir--; 
    }
}

int main() {
    int arr[7] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;

    cout << "Data Sebelum Dibalik (Nilai & Alamat):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Nilai: " << *(arr + i) << " | Alamat: " << (arr + i) << endl;
    }

    reverseArray(arr, n);

    cout << "\nData Setelah Dibalik (Nilai & Alamat):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Nilai: " << *(arr + i) << " | Alamat: " << (arr + i) << endl;
    }

    return 0;
}