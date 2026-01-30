#include <stdio.h>
#include <stdlib.h>
#include "vehicle.h"
#include "function.h"
#include "service.h"

Vehicle kendaraan;

void menuTambahKendaraan() {
    char *plat = inputPlat();
    int hasil = cariPlat(plat, &kendaraan);

    if (hasil == PLAT_TIDAK_ADA) {
        tambahKendaraan(plat);
        free(plat);
    }
    else if (hasil == PLAT_DITEMUKAN) {
        puts("Plat nomor sudah terdaftar!");
    }
}

void menuKendaraan(Vehicle *kendaraan) {
    int pilih;

    do {
        puts("=============================");
        printf("Merk        : %s\n", kendaraan->merk);
        printf("Model       : %s\n", kendaraan->model);
        printf("Tahun       : %d\n", kendaraan->tahun);
        printf("Plat Nomor  : %s\n", kendaraan->plat);
        printf("Odometer    : %d km\n", kendaraan->odometer);
        puts("=============================");
        puts("1. Cek Kondisi Kendaraan");
        puts("2. Tambah Riwayat Servis");
        puts("3. Lihat Riwayat Servis");
        puts("0. Kembali ke Menu Utama");
        printf("Pilihanmu: ");
        scanf("%d", &pilih);
        getchar();

        switch (pilih) {
        case 1:
            cekKendaraan(kendaraan);
            break;
        
        case 2:
            tambahService(kendaraan);
            break;
        
        case 3:
            lihatService(kendaraan->plat);
            break;

        case 0:
            puts("");
            break;

        default:
            puts("Input tidak valid!");
            break;
        }
    } while (pilih != 0);
}

void menuLihatKendaraan() {
    char *plat = inputPlat();
    int hasil = cariPlat(plat, &kendaraan);

    if (hasil == PLAT_DITEMUKAN) {
        updateOdometer(&kendaraan);
        menuKendaraan(&kendaraan);
    }
    else if (hasil == PLAT_TIDAK_ADA) {
        puts("Plat nomor tidak ditemukan di data!");
    }
}

void menuUtama() {
    int pilih;

    do {
        puts("=============================");
        puts("  Vehicle Care & Monitoring  ");
        puts("=============================");
        puts("1. Tambah Kendaraan");
        puts("2. Lihat Kendaraan");
        puts("0. Keluar");
        printf("Pilihanmu: ");
        scanf("%d", &pilih);
        getchar();

        switch (pilih) {
        case 1:
            menuTambahKendaraan();
            break;
        
        case 2:
            menuLihatKendaraan();
            break;
        
        case 0:
            puts("Program berakhir, jangan lupa service");
            break;

        default:
            puts("Input tidak valid!");
            break;
        }
    } while (pilih != 0);
}

int main() {
    menuUtama();
    return 0;
}