#ifndef FUNCTION_H
#define FUNCTION_H

#include "vehicle.h"

typedef enum {
    PLAT_DITEMUKAN,
    PLAT_TIDAK_ADA,
    PLAT_INVALID
} StatusPlat;

char *inputPlat();
void updateOdometer(Vehicle *kendaraan);
void statusKeBinerString (unsigned char status, char *out);
int cekPlatValid(char *plat);
StatusPlat cariPlat(char *plat, Vehicle *kendaraan);
void tulisDataKendaraan(FILE *file, Vehicle kendaraan, char status_biner[9]);
int scanDataKendaraan(char line[200], Vehicle *kendaraan, char status_biner[9]);
void ambilTanggal(char *buffer, size_t size);

#endif