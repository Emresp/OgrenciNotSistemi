//
// Created by Emre on 27.12.2025.
// //Definition folder

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "student.h"

int Menu()
{
    int secim;
    printf("-------------------------------------\n");
    printf("-------------EduScore--------------\n");
    printf("-------------------------------------\n");
    printf("-------------HOŞGELDİNİZ-------------\n");
    printf("-------------------------------------\n");
    printf("\n1-Tum liste icin\n");
    printf("2-Ogrenci Eklemek için\n");
    printf("3-Öğrenci Bul\n");
    printf("4-Listeyi Sifirlamak icin\n");
    printf("0-Cikis icin\n");
    printf("Secim:");
    scanf("%d",&secim);

    return secim; //kullanıcın yapmış olduğu seçimi dışarı verdik
}


int Dosyaoku(Ogrenci* Sinif, int kapasite)
{
    FILE* dosya;    //dosya oluşturduk
    dosya = fopen("Sinif.txt","r"); // dosyayı okuma modunda açtık

    int sayac=0;  //anlık kaç kişi olduğunu kontrol etmek için


    if (dosya != NULL)
    {
        //Tüm dosyayı açtık ve dosyadki bilgileri belleğe yerleştirdik daha rahat işlem yapabilmek için
        while(fscanf(dosya, "%s %s %lld %f %f", Sinif[sayac].name,Sinif[sayac].surname,&Sinif[sayac].id,&Sinif[sayac].vize,&Sinif[sayac].final) != EOF)
        {
            Sinif[sayac].ortalama= (float) (Sinif[sayac].vize*0.4)+(Sinif[sayac].final*0.6);
            sayac++;


            if (sayac >= kapasite)
            {
                printf("Yer kalmadi");
                break;
            }
        }
        fclose(dosya);
        printf("%d eski ogrenci yuklendi\n",sayac);
    }
    return sayac; // tüm veriler rame alındı ve anlık kişi takibi için sayacın değerini maine verdik.
}

void ogrencilistele(Ogrenci* Sinif, int sayac)
{
    int secim;

    if (sayac==0)
    {
        printf("Listede hiç öğrenci bulunmamaktadır lütfen öğrenci ekledikten sonra tekrar deneyiniz.\n");
        return;
    }

    printf("1-Okul Numarasına Göre Listele\n");
    printf("2-Ortalamaya Göre Listele\n");
    printf("Seçim:");
    scanf("%d",&secim);

    if (secim==1)
    {
        Ogrenci temp;;
        printf("------OKUL NUMARASINA GÖRE SIRALAMA------");

        for(int i=0;i<sayac;i++)
        {
            for(int j=i+1;j<sayac;j++)
            {
                if (Sinif[i].id>Sinif[j].id)
                {
                    //Yer değiştir
                    temp = Sinif[i];

                    Sinif[i] = Sinif[j];

                    Sinif[j] = temp;
                }
            }
        }
        //Tüm listeyi okuyabilmek için for açtım
        for(int i=0;i<sayac;i++)
        {
            printf("%d-) %lld numaralı %s %s adli ogrencinin ortalamasi:%.2f\n",i+1,Sinif[i].id,Sinif[i].name,Sinif[i].surname,Sinif[i].ortalama);
        }
    }

    else if (secim==2)
    {
        Ogrenci temp;
        printf("------ORTALAMAYA GÖRE SIRALAMA------");

        for(int i=0;i<sayac;i++)
        {
            for(int j=i+1;j<sayac;j++)
            {
                if (Sinif[i].ortalama<Sinif[j].ortalama)
                {
                    //yer değiştir
                    temp = Sinif[i];
                    Sinif[i]= Sinif[j];
                    Sinif[j] = temp;
                }
            }
        }
        //Tüm listeyi okuyabilmek için for açtım
        for(int i=0;i<sayac;i++)
        {
            printf("%d-) %lld numaralı %s %s adli ogrencinin ortalamasi:%.2f\n",i+1,Sinif[i].id,Sinif[i].name,Sinif[i].surname,Sinif[i].ortalama);
        }
    }
}

//Öğrenci Ekleme fonksiyonu
Ogrenci* ogrenciekle(Ogrenci* Sinif,int *sayac, int *kapasite)
{

    if (*sayac==*kapasite)
    {
        *kapasite=*kapasite * 2;
        Ogrenci* temp= (Ogrenci*)realloc(Sinif, (*kapasite) * sizeof(Ogrenci));

        if (temp==NULL)
        {
            printf("Bellekte yeteri kadar alan yok\n");
            return Sinif;
        }
        Sinif=temp;
    }



        printf("Ogrencinin adi:");
        scanf("%s",Sinif[*sayac].name);

        printf("Ogrencinin Soyadı:");
        scanf("%s",Sinif[*sayac].surname);

        printf("Ogrencinin Okul Numarası:");
        scanf("%lld",&Sinif[*sayac].id);

        printf("%lld numaralı %s %s adli ogrencinin vize notunu giriniz:",Sinif[*sayac].id,Sinif[*sayac].name,Sinif[*sayac].surname);
        scanf("%f",&Sinif[*sayac].vize);

        printf("%lld numaralı %s %s adli ogrencinin final notunu giriniz:",Sinif[*sayac].id,Sinif[*sayac].name,Sinif[*sayac].surname);
        scanf("%f",&Sinif[*sayac].final);

        //Okunabilirlik kolay olsun diye ortalmayıda atadık
        Sinif[*sayac].ortalama=(float)(Sinif[*sayac].vize*0.4)+(Sinif[*sayac].final*0.6);

        printf("%lld numaralı %s %s adli ogrencinin ortalamasi:%.2f olarak basarili sekilde kayit edilmistir\n",Sinif[*sayac].id,Sinif[*sayac].name,Sinif[*sayac].surname,Sinif[*sayac].ortalama);

        *sayac=*sayac+1;

        return Sinif;

}

void ogrenciara(Ogrenci* Sinif, int sayac)
{
    char buluncakisim[20];
    char buluncaksoyisim[20];
    int bulunanisimsirasi = 0;
    long long int buluncak_id;
    int aramasecim;

    //Arama Yöntemi
    printf("1-Hızlı Arama (sadece isim)\n"); //Sadece isime göre arama yapar o isimdeki herkesi gösterir.
    printf("2-Detaylı Arama (isim ve soyisim)\n"); // İsim ve soyisime göre arama yapar.
    printf("3-Kesin Arama (Okul Numarası)\n");
    printf("Seçim:");
    scanf("%d",&aramasecim);


    // Hızlı arama (isim)
    if (aramasecim==1)
    {
        bulunanisimsirasi = 0;
        printf("Bulmak İstediğiniz Öğrencinin İsmini Girerek Arama Yapın\n");
        printf("İsim:");
        scanf("%s",buluncakisim);


        printf("\n------%s adlı öğrenciye göre Arama sonuçları ------\n",buluncakisim);

        for(int i=0;i<sayac;i++)
        {
            //bulunursa
            if (strcmp(Sinif[i].name,buluncakisim)==0)
            {
                bulunanisimsirasi++;
                printf("%d-)%s %s Vize:%.2f Final:%.2f Ortalama:%.2f\n",bulunanisimsirasi,Sinif[i].name,Sinif[i].surname,Sinif[i].vize,Sinif[i].final,Sinif[i].ortalama);
            }

        }
    }

    else if (aramasecim==2)
    {
        bulunanisimsirasi = 0;
        printf("Bulmak İstediğiniz Öğrencinin İsmini Girin\n");
        printf("İsim:");
        scanf("%s",buluncakisim);

        printf("Bulmak İstediğiniz Öğrencinin Soyismini Girin\n");
        printf("İsim:");
        scanf("%s",buluncaksoyisim);

        printf("\n------%s %s Adlı Öğrenciye Göre Arama Sonuçları ------\n",buluncakisim,buluncaksoyisim);

        for(int i=0;i<sayac;i++)
        {

            if (strcmp(Sinif[i].name, buluncakisim) == 0 && strcmp(Sinif[i].surname, buluncaksoyisim) == 0)
            {
                bulunanisimsirasi++;
                printf("%d-)%lld Numaralı %s %s İsimli Öğrenci Bilgileri: Vize:%.2f Final:%.2f Ortalama:%.2f\n",bulunanisimsirasi,Sinif[i].id,Sinif[i].name,Sinif[i].surname,Sinif[i].vize,Sinif[i].final,Sinif[i].ortalama);
            }
        }
    }
    else if (aramasecim==3)
    {
        printf("Bulmak İstediğiniz Öğrencinin Okul Numarasını Girin\n");
        printf("Numara:");
        scanf("%lld",&buluncak_id);

        for(int i=0;i<sayac;i++)
        {
            if (buluncak_id==Sinif[i].id)
            {
                printf("1-)%lld Numaralı %s %s İsimli Öğrenci Bilgileri: Vize:%.2f Final:%.2f Ortalama:%.2f\n",Sinif[i].id,Sinif[i].name,Sinif[i].surname,Sinif[i].vize,Sinif[i].final,Sinif[i].ortalama);
            }
        }
    }
    else
    {
        printf("Girmiş Olduğunuz Bilgilere Göre Bir Öğrenci Bulunamadı Lütfen Kontrol Edip Tekrar Deneyiniz");
    }

}

int listesifirla(int anliksayac)
{
    char kontrol[20];    // lsiteyi sıfırlama işleminde 2.bir güvenlik için
    printf("Su anda listeyi sifirliyorsunuz devam etmek icin \"EMINIM\" yazın:\n");
    printf("Kontrol:");
    scanf("%s",kontrol);
    if (strcmp("EMINIM",kontrol)==0)
    {
        return 0;
    }
    else
    {
        printf("\n Kontrol mesajı doğru girilmediği için liste sıfırlanmadı\n");
        return anliksayac;
    }
}

void listekaydet(Ogrenci* Sinif,int sayac)
{
    FILE* dosya;
    dosya = fopen("Sinif.txt","w");
    for(int i=0;i<sayac;i++)
    {
        fprintf(dosya, "%s %s %lld %.2f %.2f\n",Sinif[i].name,Sinif[i].surname,Sinif[i].id,Sinif[i].vize,Sinif[i].final);
    }
    fclose(dosya);
    printf("Deftere kaydedildi");
}
