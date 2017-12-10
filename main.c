#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXSATIR 10
#define MAXSUTUN 4

typedef enum cinsiyet{E,K}cinsiyet;

typedef enum Dolu{D,B}Dolu;

typedef enum Gun{pazartesi=1,sali,carsamba,persembe,cuma,cumartesi,pazar}Gun;

typedef struct Musteri
{
    char ad[9];
    char soyad[15];
    int tcNu;
    cinsiyet cins;
}Musteri;

typedef struct Koltuk
{
    int nu;
    Dolu dolu;
    Musteri m1;
    Gun gun;
}Koltuk;

typedef struct Otobus
{
    char plaka[15];
    char marka[15];
    int model;
    Koltuk koltuk[MAXSATIR][MAXSUTUN];
}Otobus;

void koltukDurumunuDosyayaYaz(Otobus *);
void kisiArama(Otobus *);

void ekraniTemizle()
{
    system("@cls||clear");
}

void koltukSatis(Otobus *otobus)
{
    char ad[9], soyad[15];
    int tcNu, sutun, sira,sayi,cinsiyet,gun;
    puts("Musterinin adini giriniz:");
    scanf("%s",ad);
    puts("Musterinin soyadini giriniz:");
    scanf("%s",soyad);
    puts("Musterinin kimlik numarasini giriniz:");
    scanf("%d",&tcNu);
    puts("Cinsiyetinizi giriniz Erkek için 0, Kadın için 1 :");
    scanf("%d",&cinsiyet);
    puts("haftanin gununu 1 den 7 ye giriniz");
    scanf("%d",&gun);
    puts("1 den 40 a koltuk numarasını giriniz:");
    scanf("%d",&sayi);
    sira = (sayi-1)/MAXSUTUN;
    sutun = (sayi-1)%MAXSUTUN;

    while(true){
        if(otobus->koltuk[sira][sutun].dolu==B)
        {
            otobus->koltuk[sira][sutun].dolu=D;
            otobus->koltuk[sira][sutun].m1.cins = (cinsiyet == 0) ? E : K;
            otobus->koltuk[sira][sutun].m1.tcNu=tcNu;
            strcpy(otobus->koltuk[sira][sutun].m1.ad,ad);
            strcpy(otobus->koltuk[sira][sutun].m1.soyad,soyad);
            otobus->koltuk[sira][sutun].gun = gun;
            ekraniTemizle();
            puts("*****SATIS ISLEMI TAMAMLANDI*****");
            koltukDurumunuDosyayaYaz(otobus);
            break;
        }
        else {
            puts("Bu koltuk dolu lutfen baska bir koltuk giriniz");
            puts("1 den 40 a koltuk numarasını giriniz:");
            scanf("%d",&sayi);
            sira = (sayi-1)/MAXSUTUN;
            sutun = (sayi-1)%MAXSUTUN;
        }
    }
}

void otobusDurumuGoster(Otobus *otobus){
    int i,j;
    puts(otobus->plaka);
    puts(otobus->marka);
    printf("%d\nS|\t1\t2\t3\t4\n\t-\t-\t-\t-\n",otobus->model);
    for (i = 0;  i<MAXSATIR ; i++) {
        printf("%d|\t",i+1);
        for (j =0 ; j <MAXSUTUN ; ++j) {
            if (otobus->koltuk[i][j].dolu==B){
                printf("%d\t",otobus->koltuk[i][j].nu);
            }
            else if(otobus->koltuk[i][j].dolu==D){
                if(otobus->koltuk[i][j].m1.cins==E){
                    printf("%c\t",'X');
                }
                else printf("%c\t",'O');
            }
        }
        printf("\n");
    }
}

void anaEkran(Otobus *otobus)
{
    while(1){
        puts("1- Otobus Durumunu Goster");
        puts("2- Koltuk Satış");
        puts("3- Kisi Arama");
        puts("4- Cikis");
        int a;
        scanf("%d",&a);
        switch (a) {
            case 1:
                otobusDurumuGoster(otobus);
                break;
            case 2:
                koltukSatis(otobus);
                break;
            case 3:
                kisiArama(otobus);
                break;
            case 4:
                return;
            default:
                puts("yanlis giris yaptiniz");
        }
    }
}

void koltukDurumunuDosyayaYaz(Otobus *otobus){
    FILE *dosya;
    char doluluk;
    int i,j;
    dosya = fopen("otobus.txt","w");
    //fprintf(dosya,"%s %s %d\n",otobus->plaka,otobus->marka,otobus->model);
    for (i = 0;  i<MAXSATIR ; i++) {
        for (j = 0; j <MAXSUTUN ; j++) {
            fprintf(dosya,"%d %s %d %s %s %d %d\n",
                    otobus->koltuk[i][j].nu,
                    (otobus->koltuk[i][j].dolu==B) ? "B" : "D",
                    otobus->koltuk[i][j].gun,
                    otobus->koltuk[i][j].m1.ad,
                    otobus->koltuk[i][j].m1.soyad,
                    otobus->koltuk[i][j].m1.tcNu,
                    otobus->koltuk[i][j].m1.cins);
        }
    }
    fclose(dosya);
}

void bosOtobusStructiOlustur(Otobus *otobus){
    int i = 0,j,sayac=1;

    strcpy(otobus->marka, "MERCEDES");
    strcpy(otobus->plaka, "34 MR 324");
    otobus->model = 403;

    Koltuk **koltuklar = (Koltuk **)malloc(MAXSATIR* sizeof(Koltuk *));

    for (i = 0; i < MAXSATIR; i++) {
        koltuklar[i]= (Koltuk *)malloc(MAXSUTUN* sizeof(Koltuk));
    }

    for (i = 0;  i<MAXSATIR ; i++) {
        for (j = 0; j <MAXSUTUN ; j++) {
            koltuklar[i][j].nu = sayac++;
            koltuklar[i][j].m1.cins=E;
            koltuklar[i][j].m1.tcNu=25;
            strcpy(koltuklar[i][j].m1.ad,"eee");
            strcpy(koltuklar[i][j].m1.soyad,"bbb");
            koltuklar[i][j].dolu=B;
            koltuklar[i][j].gun=pazartesi;
        }
    }
    int r;
    for(r = 0; r < MAXSATIR; ++r)
        memcpy(otobus->koltuk[r], koltuklar[r], sizeof(Koltuk) * MAXSUTUN);
    koltukDurumunuDosyayaYaz(otobus);
}

void dosyadanOtobusBilgileriOku(Otobus *otobus){
        int i = 0, j = 0;
        FILE *dosya;
        dosya = fopen("otobus.txt","r");

        char *dolu=malloc(sizeof(char));

        for (i = 0;  i<MAXSATIR ; i++) {
            for (j = 0; j <MAXSUTUN ; j++) {
                fscanf(dosya,"%d %s %d %s %s %d %d\n",
                        &otobus->koltuk[i][j].nu,
                        dolu,
                        &otobus->koltuk[i][j].gun,
                        otobus->koltuk[i][j].m1.ad,
                        otobus->koltuk[i][j].m1.soyad,
                        &otobus->koltuk[i][j].m1.tcNu,
                        &otobus->koltuk[i][j].m1.cins);
                if(!strcmp(dolu,"B")){
                    otobus->koltuk[i][j].dolu=B;
                }
                else if(!strcmp(dolu,"D"))
                    otobus->koltuk[i][j].dolu=D;
            }
        }
    }

void kisiArama(Otobus *otobus){

    bool a = false;
    int tcNu=5,i,j;
    char devamMi = 'y';
    while (devamMi == 'y'){
        printf("Tc giriniz.");
        //scanf("%d",&tcNu);
        for (i = 0; i < MAXSUTUN ; i++) {
            for (j = 0; j < MAXSATIR ; j++) {
                if(otobus->koltuk[i][j].m1.tcNu==tcNu){
                    printf("\nMusteri>\n\tAd: %s\n\tSoyad: %s\n\tTc: %d",otobus->koltuk[i][j].m1.ad,otobus->koltuk[i][j].m1.soyad,otobus->koltuk[i][j].m1.tcNu);
                    a=true;
                    break;
                }
                else if(i==3 && j ==9){
                    puts("Bulunamadi");
                }
            }
            if (a == true)
                break;
        }
        puts("Yeni arama yapmak ister misiniz, y/n");
        scanf("%c",&devamMi);
    }
}

int main(void) {
    Otobus *otobus = (Otobus *)malloc(sizeof(Otobus));
    bosOtobusStructiOlustur(otobus);
    dosyadanOtobusBilgileriOku(otobus);
    anaEkran(otobus);
    return 0;
}



