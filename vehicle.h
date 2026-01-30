#ifndef VEHICLE_H
#define VEHICLE_H

typedef struct {
    char merk[20];
    char model[20];
    char plat[15];
    int tahun;
    int odometer;
    char status_komponen;
    int km_terakhir_komponen[8];
} Vehicle;

extern char *namaKomponen[8];

void cekKendaraan(Vehicle *kendaraan);
void tambahKendaraan(char *plat);
void updateDataKendaraan(Vehicle *kendaraan);
void hitungStatusKomponen(Vehicle *kendaraan);

#endif