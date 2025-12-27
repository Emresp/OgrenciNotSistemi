#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

//Kendi değişkenimi oluşturdum
typedef struct
{
    char name[20];
    char surname[20];
    float vize;
    float final;
    float ortalama;
}Ogrenci; //sturctın ismi

int main(void)
{

    //Türkçe çalışmak için
    SetConsoleOutputCP(65001); // Ekranı UTF-8
    SetConsoleCP(65001);       // Klavyeyi de UTF-8


    int kapasite=40;    //İlk başta kendi tanımladığım kapasite
    int secim;  //kullanıcının yaptırmak istediği seçimi tutar
    int sayac;  //anlık kaç kişi olduğunu kontrol etmek için
    char kontrol[7];    // lsiteyi sıfırlama işleminde 2.bir güvenlik için
    int aramasecim;

    //Öğrenci Bulma İşlemleri için
    char buluncakisim[20];
    char buluncaksoyisim[20];
    int bulunanisimsirasi=0;

    sayac=0;

    Ogrenci* Sinif; // sturcta tutcağımız bilgiler için pointer

    Sinif = (Ogrenci*)malloc(kapasite * sizeof(Ogrenci));   //sınıf için ramde yer ayırdık

    FILE* dosya;    //dosya oluşturduk

    dosya = fopen("Sinif.txt","r"); // dosyayı okuma modunda açtık

    if (dosya != NULL)
    {
        //Tüm dosyayı açtık ve dosyadki bilgileri belleğe yerleştirdik daha rahat işlem yapabilmek için
        while(fscanf(dosya, "%s %s %f %f", Sinif[sayac].name,Sinif[sayac].surname,&Sinif[sayac].vize,&Sinif[sayac].final) != EOF)
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


    //Programın hep açık kalması için sonsuz döngü kulandık
    while(1)
    {
        printf("\n1-Tum liste icin\n");
        printf("2-Ogrenci Ekle\n");
        printf("3-Listeyi Sifirlamak icin\n");
        printf("4-Öğrenci Bul\n");
        printf("0-Cikis icin\n");
        printf("Secim:");
        scanf("%d",&secim);


        if (secim==1)
        {
            if(sayac==0)
            {
                printf("Listede hiç öğrenci bulunmamaktadır lütfen öğrenci ekledikten sonra tekrar deneyiniz.\n");
            }

            else
            {
                //Tüm listeyi okuyabilmek için for açtım
                for(int i=0;i<sayac;i++)
                {
                    printf("%d-) %s %s adli ogrencinin ortalamasi:%.2f\n",i+1,Sinif[i].name,Sinif[i].surname,Sinif[i].ortalama);
                }
            }

        }


        else if (secim==2)
        {
            //Kullanıcın başta açtığı sınırı kontrol ettik
            if(sayac==kapasite)
            {
                Sinif=(Ogrenci*)realloc(Sinif,(kapasite*2)*sizeof(Ogrenci));
                kapasite=kapasite*2;
                if (Sinif==NULL)
                {
                    printf("Not enought of memory\n");
                }
            }


            //Bilgileri doldurduk
            printf("Ogrencinin adi:");
            scanf("%s",Sinif[sayac].name);

            printf("Ogrencinin Soyadı:");
            scanf("%s",Sinif[sayac].surname);

            printf("%s %s adli ogrencinin vize notunu giriniz:",Sinif[sayac].name,Sinif[sayac].surname);
            scanf("%f",&Sinif[sayac].vize);

            printf("%s %s adli ogrencinin final notunu giriniz:",Sinif[sayac].name,Sinif[sayac].surname);
            scanf("%f",&Sinif[sayac].final);

            //Okunabilirlik kolay olsun diye ortalmayıda atadık
            Sinif[sayac].ortalama=(float)(Sinif[sayac].vize*0.4)+(Sinif[sayac].final*0.6);

            printf("%s %s adli ogrencinin ortalamasi:%.2f olarak basarili sekilde kayit edilmistir\n",Sinif[sayac].name,Sinif[sayac].surname,Sinif[sayac].ortalama);

            sayac=sayac+1;
        }

        else if (secim==3)
        {
            printf("Su anda listeyi sifirliyorsunuz devam etmek icin \"EMİNİM\" yazın:\n");
            printf("Kontrol:");
            scanf("%s",kontrol);
            if (strcmp("EMİNİM",kontrol)==0)
            {
                dosya=fopen("Sinif.txt","w");
                sayac=0;
                fclose(dosya);
            }
            else
            {
                printf("\n Kontrol mesajı doğru girilmediği için liste sıfırlanmadı\n");
            }
        }

        else if (secim==4)
        {
            bulunanisimsirasi = 0;

            //Arama Yöntemi
            printf("1-Hızlı Arama (sadece isim)\n"); //Sadece isime göre arama yapar o isimdeki herkesi gösterir.
            printf("2-Detaylı Arama (isim ve soyisim)\n"); // İsim ve soyisime göre arama yapar.
            printf("Seçim:");
            scanf("%d",&aramasecim);


            // Hızlı arama (isim)
            if (aramasecim==1)
            {

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


            //Detaylı arama (isim soyisim)
            else if (aramasecim==2)
            {

                printf("\nBulmak İstediğiniz Öğrencinin İsmini Girin\n");
                printf("İsim:");
                scanf("%s",buluncakisim);

                printf("Bulmak İstediğiniz Öğrencinin Soyismini girin\n");
                printf("Soyisim:");
                scanf("%s",buluncaksoyisim);

                printf("\n------%s %s Adlı Öğrenciye Göre Arama Sonuçları ------\n",buluncakisim,buluncaksoyisim);

                for(int i=0;i<sayac;i++)
                {
                    //bulunursa
                    if (strcmp(Sinif[i].name,buluncakisim)==0&&strcmp(Sinif[i].surname,buluncaksoyisim)==0)
                    {
                        bulunanisimsirasi++;
                        printf("%d-)%s %s Vize:%.2f Final:%.2f Ortalama:%.2f\n",bulunanisimsirasi,Sinif[i].name,Sinif[i].surname,Sinif[i].vize,Sinif[i].final,Sinif[i].ortalama);

                    }
                }

            }

            if (bulunanisimsirasi==0)
            {
                printf("Girmiş olduğunuz öğrenci kriterlerine göre hiç bi öğrenci bulunamadı.");
            }

        }

        else if (secim==0 )
        {
            dosya = fopen("Sinif.txt","w");
            for(int i=0;i<sayac;i++)
            {
                fprintf(dosya, "%s %s %.2f %.2f\n",Sinif[i].name,Sinif[i].surname,Sinif[i].vize,Sinif[i].final);
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