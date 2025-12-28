#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "student.h"



int main(void)
{
    //Türkçe çalışmak için
    SetConsoleOutputCP(65001); // Ekranı UTF-8
    SetConsoleCP(65001);       // Klavyeyi de UTF-8

    int kapasite=10;    //İlk başta kendi tanımladığım kapasite
    int secim;  //kullanıcının yaptırmak istediği seçimi tutar
    int sayac;  //anlık kaç kişi olduğunu kontrol etmek için

    Ogrenci* Sinif; // sturcta tutcağımız bilgiler için pointer

    Sinif = (Ogrenci*)malloc(kapasite * sizeof(Ogrenci));   //sınıf için ramde yer ayırdık

   sayac=Dosyaoku(Sinif,kapasite);


    //Programın hep açık kalması için sonsuz döngü kulandık
    while(1)
    {
        secim=Menu();

        if (secim==1){ogrencilistele(Sinif,sayac);}

        else if (secim==2) { Sinif=ogrenciekle(Sinif,&sayac,&kapasite);}

        else if (secim==3) {ogrenciara(Sinif,sayac);}

        else if (secim==4) {sayac=listesifirla(sayac);}

        else if (secim==5){basarianalizi(Sinif,sayac);}

        else if (secim==0 ) {listekaydet(Sinif,sayac); break;}

        else
        {
            printf("Lütfen Geçerli Bir Seçim Yapınız");
        }

    }

    // RAM'de açtığımız alanı serbest bıraktık
    free(Sinif);
    return 0;
}