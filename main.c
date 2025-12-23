#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[20];
    int vize;
    int final;
    int ortalama;
}Ogrenci;

int main(void)
{
    int kisisayisi;
    int secim;
    int sayac;

    sayac=0;

    printf("Kac kisilik liste olusturmak istiyorsunuz:");
    scanf("%d",&kisisayisi);

    // bu kullanım şekli tehlikelidir büyük sayılarda overflow hatası verebilir KULLANMA (Ogrenci Sinif[kisisayisi]);

    Ogrenci* Sinif;

    Sinif = (Ogrenci*)malloc(kisisayisi * sizeof(Ogrenci));

    FILE* dosya;

    dosya = fopen("Sinif.txt","r");

    if (dosya != NULL)
    {
        while(fscanf(dosya, "%s %d %d", Sinif[sayac].name, &Sinif[sayac].vize,&Sinif[sayac].final) != EOF)
        {
            Sinif[sayac].ortalama=(Sinif[sayac].vize*0.4)+(Sinif[sayac].final*0.6);
            sayac++;


            if (sayac >= kisisayisi)
            {
                printf("Yer kalmadi");
                break;
            }
        }
        fclose(dosya);
        printf("%d eski ogrenci yuklendi\n",sayac);
    }


    //Programın hep açık kalması için sonsuz döngü kulandık
    while(1)
    {
        printf("\n1-Tum liste icin\n");
        printf("2-Ogrenci Ekle\n");
        printf("0-Cikis icin\n");
        printf("Secim:");
        scanf("%d",&secim);


        if (secim==1)
        {
            //Tüm listeyi okuyabilmek için for açtım
            for(int i=0;i<sayac;i++)
            {
                printf("%d-) %s adli ogrencinin ortalamasi:%d\n",i+1,Sinif[i].name,Sinif[i].ortalama);
            }
        }


        else if (secim==2)
        {
            //Kullanıcın başta açtığı sınırı kontrol ettik
            if(sayac==kisisayisi)
            {
                printf("Tanimladiginiz sinif listesi dolmustur\n");
                continue;
            }


            //Bilgileri doldurduk
            printf("Ogrencinin adi:");
            scanf("%s",&Sinif[sayac].name);

            printf("%s adli ogrencinin vize notunu giriniz:",Sinif[sayac].name);
            scanf("%d",&Sinif[sayac].vize);

            printf("%s adli ogrencinin final notunu giriniz:",Sinif[sayac].name);
            scanf("%d",&Sinif[sayac].final);

            //Okunabilirlik kolay olsun diye ortalmayıda atadık
            Sinif[sayac].ortalama=(Sinif[sayac].vize*0.4)+(Sinif[sayac].final*0.6);

            printf("%s adli ogrencinin ortalamasi:%d olarak basarili sekilde kayit edilmistir\n",Sinif[sayac].name,Sinif[sayac].ortalama);

            sayac=sayac+1;
        }

        else if (secim==0 )
        {
            dosya = fopen("Sinif.txt","w");
            for(int i=0;i<sayac;i++)
            {
                fprintf(dosya, "%s %d %d\n",Sinif[i].name,Sinif[i].vize,Sinif[i].final);
            }
            fclose(dosya);
            printf("Deftere kaydedildi");
            break;
        }

        else printf("Lutfen Gecerli Bir Secim Yapiniz\n");
    }

    // RAM'de açtığımız alanı serbest bıraktık
    free(Sinif);
    return 0;
}