#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "function.h"
#include "vehicle.h"

char *inputPlat() {
    char *plat = malloc(15 * sizeof(char));

    printf("Masukkan plat nomor kendaraan (tanpa spasi): ");
    fgets(plat, 15, stdin);
    plat[strcspn(plat, "\n")] = '\0';

    return plat;
}

void updateOdometer(Vehicle *kendaraan) {
    int odometer = 0;

    do {
        printf("Masukkan odometer sekarang (km): ");
        scanf("%d", &odometer);
        if (odometer < kendaraan->odometer) {
            puts("Odometer tidak boleh lebih kecil dari sebelumnya!");
        }
    } while (odometer < kendaraan->odometer);
    kendaraan->odometer = odometer;
    updateDataKendaraan(kendaraan);
}

void statusKeBinerString (unsigned char status, char *out) {
    for (int i = 7; i >= 0; i--) {
        out[7 - i] = (status & (1 << i)) ? '1' : '0';
    }
    out[8] = '\0';
}

int cekPlatValid(char *plat) {
    int i = 0;

    int kode_daerah = 0;
    while (isupper(plat[i])) {
        kode_daerah++;
        i++;
    }
    if (kode_daerah < 1 || kode_daerah > 2)
        return 0;

    int digitCount = 0;
    while (isdigit(plat[i])) {
        digitCount++;
        i++;
    }
    if (digitCount < 1 || digitCount > 4)
        return 0;

    int hurufCount = 0;
    while (isupper(plat[i])) {
        hurufCount++;
        i++;
    }
    if (hurufCount < 2 || hurufCount > 3)
        return 0;
    
    return plat[i] == '\0';
}

StatusPlat cariPlat(char *plat, Vehicle *kendaraan) {
    if (cekPlatValid(plat)) {
        FILE *fp = fopen("data kendaraan.txt", "r");
        if (!fp) {
            puts("Gagal membuka file!");
            return 0;
        }

        char line[200];
        while (fgets(line, sizeof(line), fp)) {
            Vehicle v;

            char status_biner[9];
            if (scanDataKendaraan(line, &v, status_biner)) {
                continue;
            }

            v.status_komponen = (unsigned char)strtol(status_biner, NULL, 2);

            if (strcmp(v.plat, plat) == 0) {
                *kendaraan = v;
                fclose(fp);
                return PLAT_DITEMUKAN;
            }

        }

        fclose(fp);
        return PLAT_TIDAK_ADA;
    }
    else {
        puts("Plat tidak valid!");
        return PLAT_INVALID;
    }
}

void tulisDataKendaraan(FILE *file, Vehicle kendaraan, char status_biner[9]) {
    fprintf(file, "%s|%s|%d|%s|%d|%s", kendaraan.merk, kendaraan.model, kendaraan.tahun, kendaraan.plat, kendaraan.odometer, status_biner);

    for (int i = 0; i < 8; i++) {
        fprintf(file, "|%d", kendaraan.km_terakhir_komponen[i]);
    }
    fprintf(file, "\n");
}

int scanDataKendaraan(char line[200], Vehicle *kendaraan, char status_biner[9]) {
    if (sscanf(line, "%19[^|]|%19[^|]|%d|%14[^|]|%d|%8s|%d|%d|%d|%d|%d|%d|%d|%d",
            kendaraan->merk, kendaraan->model, &kendaraan->tahun, kendaraan->plat, &kendaraan->odometer, status_biner,
            &kendaraan->km_terakhir_komponen[0],
            &kendaraan->km_terakhir_komponen[1],
            &kendaraan->km_terakhir_komponen[2],
            &kendaraan->km_terakhir_komponen[3],
            &kendaraan->km_terakhir_komponen[4],
            &kendaraan->km_terakhir_komponen[5],
            &kendaraan->km_terakhir_komponen[6],
            &kendaraan->km_terakhir_komponen[7]) != 14) {
        return 1;
    }
    return 0;
}

void ambilTanggal(char *buffer, size_t size) {
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    strftime(buffer, size, "%Y-%m-%d", tm_info);
}