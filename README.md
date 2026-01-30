# Vehicle Care & Monitoring

Aplikasi berbasis Command Line Interface (CLI) yang ditulis dalam bahasa C untuk membantu pemilik kendaraan memantau kondisi komponen kendaraan berdasarkan jumlah kilometer (odometer). Program ini akan memberikan peringatan jika suatu komponen sudah memasuki masa servis atau perlu diganti.

## Deskripsi Proyek

Program ini dirancang untuk mencatat data kendaraan, melacak riwayat servis, dan menghitung status kesehatan komponen secara otomatis. Dengan membandingkan odometer saat ini dengan kilometer terakhir kali komponen diservis, sistem dapat menentukan apakah komponen tersebut masih aman atau memerlukan tindakan perawatan.

## Fitur Utama

* **Manajemen Kendaraan**: Menambah data kendaraan baru (merk, model, tahun, plat nomor) dan menyimpan informasi odometer awal.
* **Monitoring Kondisi Komponen**: Mengecek 8 komponen utama secara otomatis: Oli Mesin, Rem, Ban, Shock, Aki, Lampu, Busi, dan Injeksi.
* **Pembaruan Odometer**: Memperbarui kilometer kendaraan secara berkala untuk mendapatkan analisis kondisi terbaru.
* **Riwayat Servis**: Mencatat detail setiap servis yang dilakukan (tanggal, odometer, jenis servis, dan catatan tambahan) ke dalam file teks.
* **Penyimpanan Data**: Seluruh data kendaraan dan riwayat servis disimpan secara permanen dalam file `.txt` (`data kendaraan.txt` dan `riwayat service.txt`).

## Komponen & Interval Servis

Sistem menggunakan standar interval berikut untuk menentukan status komponen:
1.  **Oli Mesin**: 3.000 km
2.  **Ban**: 15.000 km
3.  **Injeksi**: 15.000 km
4.  **Rem, Shock, Aki, Busi**: 20.000 km
5.  **Lampu**: 10.000 km

## Cara Menjalankan Program

### Prasyarat
* GCC Compiler (MinGW untuk Windows).
* Sistem Operasi Windows/Linux/macOS.

### Langkah-langkah
1.  **Clone Repositori**:
    ```bash
    git clone [https://github.com/username/Vehicle-Care-Monitoring.git](https://github.com/username/Vehicle-Care-Monitoring.git)
    cd Vehicle-Care-Monitoring
    ```

2.  **Kompilasi Program**:
    Gunakan perintah berikut untuk mengompilasi seluruh file sumber:
    ```bash
    gcc main.c function.c service.c vehicle.c -o program
    ```

3.  **Jalankan Aplikasi**:
    ```bash
    ./program
    ```

## Struktur File
* `main.c`: Alur utama program dan menu navigasi.
* `vehicle.c/h`: Logika pengelolaan data kendaraan dan pengecekan kondisi.
* `service.c/h`: Logika penambahan dan pemanggilan riwayat servis.
* `function.c/h`: Fungsi utilitas seperti input plat dan pengelolaan file.
* `data kendaraan.txt`: Database kendaraan yang terdaftar.
* `riwayat service.txt`: Database catatan servis kendaraan.
