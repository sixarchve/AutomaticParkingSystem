# ESP-WROOM-32 Automated Parking System (APS)

![ESP-WROOM-32](https://img.shields.io/badge/ESP32-WROOM--32-blue)
![Arduino IDE](https://img.shields.io/badge/IDE-Arduino-green)
![License](https://img.shields.io/badge/License-MIT-yellow)

Proyek ini adalah sistem parkir otomatis berbasis ESP32 yang mengintegrasikan RFID untuk autentikasi, servo untuk pembukaan palang, serta sensor dan LED untuk indikasi status parkir. Dikembangkan menggunakan **Arduino IDE** dengan tambahan beberapa library khusus.

## Fitur
- **RFID Authentication**: Hanya kartu RFID yang terdaftar yang dapat mengakses parkir.
- **Automated Servo Gate**: Palang parkir yang dikontrol dengan servo.
- **Parking Slot Monitoring**: Indikator LED untuk menunjukkan status slot parkir (kosong atau penuh).
- **Obstacle Detection**: Sensor untuk mendeteksi keberadaan kendaraan di jalur masuk.

## Kebutuhan Sistem
- Mikrokontroler: ESP-WROOM-32.
- Perangkat tambahan:
  - RFID reader (MFRC522).
  - Servo motor.
  - Sensor penghalang.
  - LED indikator.

## Library yang Dibutuhkan
Instal library berikut melalui **Tools > Manage Libraries** di Arduino IDE, atau unduh langsung dari GitHub:

- [ESP32Servo](https://github.com/madhephaestus/ESP32Servo) oleh Kevin: Library untuk mengontrol servo motor pada ESP32.
- [MFRC522](https://github.com/miguelbalboa/rfid) oleh komunitas GitHub: Library untuk membaca dan menulis data pada modul RFID RC522.


## Instalasi dan Konfigurasi
1. **Konfigurasi Arduino IDE**:
   - Instal [Arduino IDE](https://www.arduino.cc/en/software) jika belum tersedia.
   - Tambahkan dukungan board ESP32 dengan mengikuti [panduan ini](https://github.com/espressif/arduino-esp32#installation-instructions).

2. **Library yang Dibutuhkan**:
   - Instal library berikut melalui **Tools > Manage Libraries** di Arduino IDE:
     - `ESP32Servo`
     - `MFRC522`

3. **Koneksi Perangkat Keras**:
   - Sambungkan komponen sesuai skema berikut:
     - **RFID Reader (MFRC522)**:
       - RST: GPIO 22
       - SDA: GPIO 21
       - MOSI: GPIO 23
       - MISO: GPIO 19
       - SCK: GPIO 18
       - VCC: 3.3V
       - GND: GND
     - **Servo**: GPIO 32.
     - **Sensor Penghalang**: GPIO 14.
     - **LED Indikator**:
       - Masuk Hijau: GPIO 2.
       - Masuk Merah: GPIO 15.
       - Parkir 1: GPIO 17.
       - Parkir 2: GPIO 16.

## Cara Menggunakan
1. **Unggah Program**:
   - Sambungkan ESP32 ke komputer menggunakan kabel USB.
   - Buka file `.ino` dari repositori ini di Arduino IDE.
   - Pilih board **ESP32 Dev Module** dan port yang sesuai dari menu **Tools**.
   - Klik tombol **Upload** untuk mengunggah kode ke ESP32.

2. **Operasikan Sistem**:
   - Dekatkan kartu RFID ke reader untuk membuka palang parkir.
   - Palang akan otomatis menutup setelah kendaraan masuk.
   - LED indikator akan menunjukkan status slot parkir.

## Dokumentasi Hasil
### Foto Proyek

![Foto Proyek](https://i.giphy.com/lprIQG8Pl3T4gktKOZ.webp)

![Demo GIF](https://i.giphy.com/lprIQG8Pl3T4gktKOZ.webp)


---

💡 **Hubungi**: Untuk pertanyaan lebih lanjut, silakan buat *issue* atau hubungi melalui [email](mailto:alfansyurikhaif@gmail.com).
