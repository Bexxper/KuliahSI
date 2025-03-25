#include <stdio.h>
#include <stdlib.h>

// Definisikan struktur menu
typedef struct {
    int id;
    char nama[20];
    int harga;
} Menu;

// Definisikan struktur antrian
typedef struct {
    int data[10];
    int depan, belakang;
} Antrian;

// Fungsi untuk menginisialisasi antrian
void initAntrian(Antrian *a) {
    a->depan = a->belakang = 0;
}

// Fungsi untuk menambahkan elemen ke antrian
void tambahAntrian(Antrian *a, int data) {
    a->data[a->belakang++] = data;
}

// Fungsi untuk menghapus elemen dari antrian
int hapusAntrian(Antrian *a) {
    return a->data[a->depan++];
}

// Fungsi untuk menampilkan menu
void tampilkanMenu(Menu menu[], int n) {
    printf("Menu:\n");
    for (int i = 0; i < n; i++) {
        printf("%d. %s - Rp %d\n", menu[i].id, menu[i].nama, menu[i].harga);
    }
}

// Fungsi untuk mengurutkan menu berdasarkan harga
void urutkanMenu(Menu menu[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (menu[i].harga > menu[j].harga) {
                Menu temp = menu[i];
                menu[i] = menu[j];
                menu[j] = temp;
            }
        }
    }
}

// Fungsi untuk menghasilkan nomor meja menggunakan grafik statis
int hasilkanNomorMeja() {
    static int nomorMeja = 1;
    return nomorMeja++;
}

int main() {
    // Inisialisasi array menu
    Menu menu[] = {
        {5, "Nasi goreng", 12000},
        {3, "Mie goreng", 10000},
        {4, "Ayam geprek", 10000},
        {1, "Ice tea", 5000},
        {2, "Lemon tea", 5000}
    };
    int n = sizeof(menu) / sizeof(menu[0]);

    // Urutkan menu berdasarkan harga
    urutkanMenu(menu, n);

    // Inisialisasi antrian
    Antrian a;
    initAntrian(&a);

    // Tampilkan menu
    tampilkanMenu(menu, n);

    // Dapatkan pilihan pengguna
    int pilihan[10];
    int i = 0;
    printf("Pilih menu (masukkan 0 untuk selesai): ");
    while (1) {
        scanf("%d", &pilihan[i]);
        if (pilihan[i] == 0) break;
        tambahAntrian(&a, pilihan[i]);
        i++;
    }

    // Tampilkan antrian
    printf("Pilihan Anda:\n");
    int total = 0;
    for (int j = 0; j < i; j++) {
        printf("%d. %s - Rp %d\n", pilihan[j], menu[pilihan[j] - 1].nama, menu[pilihan[j] - 1].harga);
        total += menu[pilihan[j] - 1].harga;
    }

    // Tampilkan total harga
    printf("Total harga: Rp %d\n", total);

    // Hasilkan nomor meja
    int nomorMeja = hasilkanNomorMeja();
    printf("Nomor meja Anda adalah: %d\n", nomorMeja);

    return 0;
}