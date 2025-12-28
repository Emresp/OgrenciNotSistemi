//
// Created by Emre on 27.12.2025.
//Description folder

#ifndef EDUSCORE_STUDENT_H
#define EDUSCORE_STUDENT_H

//Kendi değişkenimi oluşturdum
typedef struct
{
    char name[20];
    char surname[20];
    long long int  id;
    float vize;
    float final;
    float ortalama;
}Ogrenci; //sturctın ismi


int Menu();
int Dosyaoku(Ogrenci* Sinif, int kapasite); //Programı açınca tüm verileri rame almak için dosya oku
void ogrencilistele(Ogrenci* Sinif, int sayac);
Ogrenci* ogrenciekle(Ogrenci* Sinif,int *sayac, int *kapasite);
void ogrenciara(Ogrenci* Sinif, int sayac);
int listesifirla(int anliksayac);
void listekaydet(Ogrenci* Sinif,int sayac);
void basarianalizi(Ogrenci* Sinif,int sayac);

//EK HİZMETLER RENKLİ YAZI
void RenkliYazdir(char* metin, int renkKodu);



#endif //EDUSCORE_STUDENT_H