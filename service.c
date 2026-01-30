#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "function.h"
#include "service.h"
#include "vehicle.h"

char jenis_service[8][30] = {
    "Ganti Oli",
    "Servis Rem",
    "Ganti Ban",
    "Servis Shock",
    "Ganti Aki",
    "Ganti Lampu",
    "Ganti Busi",
    "Servis Injeksi"
};

int intervalServis[8] = {
    3000,  // Oli
    20000, // Rem
    15000, // Ban
    20000, // Shock
    20000, // Aki
    10000, // Lampu
    20000, // Busi
    15000  // Injeksi
};

void tambahService(Vehicle *kendaraan) {
    int jumlah_servis = 0;
    int pilih[8];
    Service s;

    puts("=============================");
    for (int j = 0; j < 8; j++) {
        printf("%d. %s\n", j + 1, jenis_service[j]);
    }
    printf("\nBerapa jenis servis?: ");
    scanf("%d", &jumlah_servis);

    for (int i = 0; i < jumlah_servis; i++) {
        puts("=============================");
        for (int j = 0; j < 8; j++) {
            printf("%d. %s\n", j + 1, jenis_service[j]);
        }
        printf("Pilihanmu: ");
        scanf("%d", &pilih[i]);
    }

    FILE *fs = fopen("riwayat service.txt", "a");
    if (!fs) {
        puts("Gagal membuka file!");
        return;
    }

    s.keterangan = malloc(50);
    printf("Tambahkan keterangan: ");
    getchar();
    fgets(s.keterangan, 50, stdin);
    s.keterangan[strcspn(s.keterangan, "\n")] = '\0';
    s.odometer = kendaraan->odometer;

    ambilTanggal(s.tanggal, sizeof(s.tanggal));

    fprintf(fs, "%s|%s|%d", kendaraan->plat, s.tanggal, s.odometer);
    for (int i = 0; i < jumlah_servis; i++) {
        fprintf(fs, "|%s", jenis_service[pilih[i] - 1]);
        kendaraan->km_terakhir_komponen[pilih[i] - 1] = kendaraan->odometer;
    }
    fprintf(fs, "|%s\n", s.keterangan);
    fclose(fs);
    free(s.keterangan);

    updateDataKendaraan(kendaraan);

    puts("Riwayat servis berhasil ditambahkan!");
}

void lihatService(char *plat) {
    FILE *fs = fopen("riwayat service.txt", "r");
    if (!fs) {
        puts("Gagal membuka file!");
        return;
    }

    char line[300];
    int ketemu = 0;

    puts("\n=== RIWAYAT SERVIS KENDARAAN ===");

    while (fgets(line, sizeof(line), fs)) {
        char buffer[300];
        strcpy(buffer, line);

        char *token = strtok(buffer, "|");
        if (!token) continue;

        if (strcmp(token, plat) != 0)
            continue;

        ketemu = 1;

        char tanggal[11];
        int odometer;

        token = strtok(NULL, "|");
        strcpy(tanggal, token);

        token = strtok(NULL, "|");
        odometer = atoi(token);

        printf("\nTanggal  : %s\n", tanggal);
        printf("Odometer : %d km\n", odometer);
        puts("Servis   :");

        char *servis[10];
        int jumlah_servis = 0;

        while ((token = strtok(NULL, "|")) != NULL) {
            servis[jumlah_servis++] = token;
        }

        if (jumlah_servis > 0) {
            for (int i = 0; i < jumlah_servis - 1; i++) {
                printf(" - %s\n", servis[i]);
            }
            printf("Catatan  : %s\n", servis[jumlah_servis - 1]);
        }

        puts("-----------------------------");
    }

    if (!ketemu) {
        puts("Belum ada riwayat servis untuk kendaraan ini.");
    }

    fclose(fs);
}