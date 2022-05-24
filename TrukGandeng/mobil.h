// Nama File : truk.cpp
// Deskripsi : modul truk
// Tanggal : Senin, 23 Mei 2022
// Lab : GKV A2

#ifndef MOBIL_H
#define MOBIL_H
class Halangan {
public:
    float posisiZMobil;
    float posisiXMobil;
    void cylinder(float alas, float atas, float tinggi);
    void kerucut(float bawah, float atas, float panjang);
    void blok(float tebal, int ratiol, int ratiop);
    void Mobil(float r, float g, float b);
    void Cone();
    void sisiCone();
};




#endif /* mobil_h */
