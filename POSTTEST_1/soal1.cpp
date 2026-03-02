#include <iostream>
using namespace std;

int main() {
    int arr[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int n = 8;
    
    int nilaiMin = arr[0];
    int letakIndex = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i] < nilaiMin) {
            nilaiMin = arr[i];
            letakIndex = i;
        }
    }

    cout << "Nilai Terkecil : " << nilaiMin << endl;
    cout << "Ada di Indeks  : " << letakIndex << endl;

    return 0;
}

/* Analisis
-----------------------------------------------------------------
Baris Kode                        | Nama Langkah | Jumlah Kerja 
-----------------------------------------------------------------
int nilaiMin = arr[0]             | Langkah 1    | 1 kali
int letakIndex = 0                | Langkah 2    | 1 kali
for (int i = 1; i < n; i++)       | Langkah 3    | n kali
if (arr[i] < nilaiMin)            | Langkah 4    | n-1 kali
nilaiMin = arr[i]                 | Langkah 5    | 0 s/d n-1
letakIndex = i                    | Langkah 6    | 0 s/d n-1
-----------------------------------------------------------------

Cara ngitungnya gini:

1. Kalau Lagi Beruntung (Best Case):
Ini kejadian kalau angka paling kecil udah ada di depan (indeks 0). 
Jadi, komputer cuma lewat aja tapi nggak perlu ganti-ganti isi 
variabel nilaiMin (Langkah 5 dan 6 nggak jalan atau 0).
Tmin(n) = 1 + 1 + n + (n-1) + 0 + 0 
Tmin(n) = 2n + 1
Disederhanain jadi Big-O = O(n).

2. Kalau Lagi Apes (Worst Case):
Ini kejadian kalau angkanya makin ke kanan makin kecil (kebalik). 
Komputer jadi kerja rodi karena setiap langkah harus ganti isi 
variabel terus (Langkah 5 dan 6 jalan terus).
Tmax(n) = 1 + 1 + n + (n-1) + (n-1) + (n-1)
Tmax(n) = 2 + n + 3n - 3
Tmax(n) = 4n - 1
Disederhanain jadi Big-O = O(n).

Kesimpulannya:
Mau datanya rapi atau berantakan, algoritma ini tetep "Linear" (O(n)). 
Artinya, waktu yang dibutuhin komputer bakal nambah terus sejalan sama 
banyaknya data (n) yang kita masukin. Karena n cuma pangkat 1, 
bukan n pangkat 2, jadi masih tergolong kenceng.
*/