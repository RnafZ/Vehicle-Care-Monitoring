#ifndef SERVICE_H
#define SERVICE_H

#include "vehicle.h"

typedef struct {
    char *keterangan;
    char tanggal[11];
    int odometer;
} Service;

extern char jenis_service[8][30];
extern int intervalServis[8];

void tambahService(Vehicle *kendaraan);
void lihatService(char *plat);

#endif