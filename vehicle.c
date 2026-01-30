#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "vehicle.h"
#include "function.h"
#include "service.h"

char *namaKomponen[8] = {
    "Oli Mesin",
    "Rem",
    "Ban",
    "Shock",
    "Aki",
    "Lampu",
    "Busi",
    "Injeksi"
};

void cekKendaraan(Vehicle *kendaraan) {

    hitungStatusKomponen(kendaraan);

    puts("\n=== HASIL CEK KONDISI KENDARAAN ===");
    printf("Plat      : %s\n", kendaraan->plat);
    printf("Odometer  : %d km\n\n", kendaraan->odometer);

    for (int i = 0; i < 8; i++) {
        if (kendaraan->status_komponen & (1 << i)) {
            printf("%-10s : PERLU DIGANTI/SERVIS\n", namaKomponen[i]);
        }
        else {
            printf("%-10s : AMAN\n", namaKomponen[i]);
        }
    }
    puts("");
}

void tambahKendaraan(char *plat) {
    Vehicle v;

    FILE *fp = fopen("data kendaraan.txt", "a");
    if (!fp) {
        puts("Gagal membuka file!");
        return;
    }
    
    printf("Masukkan merk, model, dan tahun kendaraan (dipisah spasi): ");
    scanf("%s %s %d", v.merk, v.model, &v.tahun);
    getchar();
    strcpy(v.plat, plat);
    printf("Masukkan odometer saat ini (km): ");
    scanf("%d", &v.odometer);

    puts("\n=== CEK KONDISI KOMPONEN ===");
    for (int i = 0; i < 8; i++) {
        printf("KM terakhir ganti/servis %s: ", namaKomponen[i]);
        scanf("%d", &v.km_terakhir_komponen[i]);
    }

    hitungStatusKomponen(&v);

    char status_biner[9];
    statusKeBinerString(v.status_komponen, status_biner);

    tulisDataKendaraan(fp, v, status_biner);

    fclose(fp);
    puts("Kendaraan berhasil ditambahkan!");
}

void updateDataKendaraan(Vehicle *kendaraan) {
    FILE *fp = fopen("data kendaraan.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!fp || !temp) {
        puts("Gagal membuka file!");
        return;
    }

    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        Vehicle v;

        char status_biner[9];
        if (scanDataKendaraan(line, &v, status_biner)) {
            continue;
        }
        
        if (strcmp(v.plat, kendaraan->plat) == 0) {
            v.odometer = kendaraan->odometer;
            
            for (int i = 0; i < 8; i++) {
                v.km_terakhir_komponen[i] = kendaraan->km_terakhir_komponen[i];
            }
            hitungStatusKomponen(&v);
            statusKeBinerString(v.status_komponen, status_biner);
        }

        tulisDataKendaraan(temp, v, status_biner);

    }

    fclose(fp);
    fclose(temp);

    remove("data kendaraan.txt");
    rename("temp.txt", "data kendaraan.txt");                      
}

void hitungStatusKomponen(Vehicle *kendaraan) {
    kendaraan->status_komponen = 0;

    for (int i = 0; i < 8; i++) {
        if (intervalServis[i] <= 0)
            continue;

        if (kendaraan->odometer - kendaraan->km_terakhir_komponen[i] >= intervalServis[i]) {
            kendaraan->status_komponen |= (1 << i);
        }
    }
}