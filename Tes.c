#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struktur untuk menu
typedef struct {
    char namaMakanan[20];
    int harga;
} Menu;

// Struktur untuk antrian
typedef struct {
    int nomorPesanan;
    char namaPelanggan[20];
    int hargaPesanan;
} Pesanan;

// Array untuk menu
Menu menu[] = {
    {"Nasi Goreng", 12000},
    {"Mie Goreng", 10000},
    {"Ayam Geprek", 10000},
    {"Ice Tea", 5000},
    {"Lemon tea", 5000}
};

// Queue untuk antrian
int depan = 0;
int belakang = 0;
Pesanan antrian[100];

// Fungsi untuk menambahkan antrian
void tambahAntrian(int nomorPesanan, char namaPelanggan[20], int hargaPesanan) {
    antrian[belakang].nomorPesanan = nomorPesanan;
    strcpy(antrian[belakang].namaPelanggan, namaPelanggan);
    antrian[belakang].hargaPesanan = hargaPesanan;
    belakang = (belakang + 1) % 100;
}

// Fungsi untuk menghapus antrian
void hapusAntrian() {
    if (depan == belakang) {
        printf("Antrian kosong!\n");
    } else {
        depan = (depan + 1) % 100;
    }
}

// Fungsi untuk menampilkan antrian
void tampilkanAntrian() {
    int i;
    printf("Antrian:\n");
    for (i = depan; i != belakang; i = (i + 1) % 100) {
        printf("Nomor Pesanan: %d, Pelanggan: %s, Harga Pesanan: %d\n", antrian[i].nomorPesanan, antrian[i].namaPelanggan, antrian[i].hargaPesanan);
    }
    printf("\n");
}

// Fungsi untuk sorting harga menu
void sortingHarga() {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = i + 1; j < 5; j++) {
            if (menu[i].harga > menu[j].harga) {
                Menu temp = menu[i];
                menu[i] = menu[j];
                menu[j] = temp;
            }
        }
    }
}

// Fungsi untuk menampilkan menu
void tampilkanMenu() {
    int i;
    printf("Menu:\n");
    for (i = 0; i < 5; i++) {
        printf("%s: Rp. %d\n", menu[i].namaMakanan, menu[i].harga);
    }
    printf("\n");
}

// Fungsi utama
int main() {
    int nomorMeja, pilihan;
    char namaPelanggan[20];
    int hargaPesanan;
    int nomorAntrian = 1;

    // Sorting harga menu
    sortingHarga();

    // Menampilkan menu
    tampilkanMenu();

    // Pelanggan melakukan scan barcode
    printf("Silakan pilih menu:\n");
    scanf("%d", &pilihan);
    printf("Masukkan nama Anda: ");
    scanf("%s", namaPelanggan);
    printf("Masukkan nomor meja: ");
    scanf("%d", &nomorMeja);

    // Menambahkan antrian
    tambahAntrian(nomorAntrian, namaPelanggan, menu[pilihan - 1].harga);
    printf("Nomor antrian Anda adalah %d.\n", nomorAntrian);

    // Menampilkan antrian
    tampilkanAntrian();

    return 0;
}