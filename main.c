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

Musteri musteriOlustur(char adi[9],char soyadi[15],int tcNusu)
{
    Musteri mu;
    strcpy(mu.ad,adi);
    strcpy(mu.soyad,soyadi);
    mu.tcNu=tcNusu;
    return mu;
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
            otobus->koltuk[sira][sutun].dolu==D;
            otobus->koltuk[sira][sutun].m1.cins = (cinsiyet == 0) ? E : K;
            otobus->koltuk[sira][sutun].m1.tcNu=tcNu;
            strcpy(otobus->koltuk[sira][sutun].m1.ad,ad);
            strcpy(otobus->koltuk[sira][sutun].m1.soyad,soyad);
            otobus->koltuk[sira][sutun].gun = gun;
            puts("Satis islemi tamamlandi");
            break;
        }
        else {
            puts("Bu koltuk dolu lutfen baska bir koltuk giriniz");
            puts("0 dan 3 e koltuk sutununu giriniz:");
            scanf("%d",&sutun);
            puts("0 dan 9 a koltuk sirasini giriniz:");
            scanf("%d",&sira);
        }
    }
}

void otobusDurumuGoster(Otobus *otobus){
    int sayac;
    int i,j;
    puts(otobus->plaka);
    puts(otobus->marka);
    printf("%d\n\n",otobus->model);


    for (i = 0;  i<MAXSATIR ; i++) {
        printf("%d|\t",i);
        for (j =0 ; j <MAXSUTUN ; ++j) {
            //printf("%d\t",45);
            printf("%s\t",(otobus->koltuk[i][j].dolu==B) ? otobus->koltuk[i][j].m1.ad : otobus->koltuk[i][j].m1.soyad);
        }
        printf("\n");
    }

}

void anaEkran(Otobus *otobus)
{
    while(1){
        puts("1- Otobus Durumunu Goster");
        puts("2- Koltuk Satıs");
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
                break;
            case 4:
                return;
            default:
                puts("yanlis giris yaptiniz");
        }
    }
}

void otobusBilgileriniYaz(Otobus otobus){
    FILE *dosya;
    if( ( dosya=fopen("otobus.txt","w") ) == NULL){
        puts("dosya işlemi yapılamadı.");

    }
    else{
        dosya = fopen("otobus.txt","w");

        fclose(dosya);
    }
}

void koltukDurumunuDosyayaYaz(Otobus *otobus){
    FILE *dosya;
    char doluluk;
    int i,j;
    dosya = fopen("otobus.txt","w");
    fprintf(dosya,"%s/%s/%d\n",otobus->plaka,otobus->marka,otobus->model);
    for (i = 0;  i<MAXSATIR ; i++) {
        for (j = 0; j <MAXSUTUN ; j++) {
            fprintf(dosya,"%d/%c/%d/%s/%s/%d/%d\n",
                    otobus->koltuk[i][j].nu,
                    (otobus->koltuk[i][j].dolu==B) ? 'B' : 'D',
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

    Koltuk ** koltuklar = (Koltuk **)malloc(MAXSATIR* sizeof(Koltuk *));
    for (i = 0; i < MAXSATIR; i++) {
        koltuklar[i]= (Koltuk *)malloc(MAXSUTUN* sizeof(Koltuk));
    }


    for (i = 0;  i<MAXSATIR ; i++) {
        for (j = 0; j <MAXSUTUN ; j++) {
            koltuklar[i][j].nu = sayac++;
            koltuklar[i][j].m1.cins=0;
            koltuklar[i][j].m1.tcNu=44444;
            strcpy(koltuklar[i][j].m1.ad,"eee");
            strcpy(koltuklar[i][j].m1.soyad,"fff");
            koltuklar[i][j].dolu=B;
            koltuklar[i][j].gun=pazartesi;
        }
    }
    memcpy(otobus->koltuk, koltuklar, sizeof(koltuklar));
    //free(koltuklar);
    koltukDurumunuDosyayaYaz(otobus);
}

int main(void) {
    Otobus *otobus = (Otobus *)malloc(sizeof(Otobus));

    bosOtobusStructiOlustur(otobus);
    anaEkran(otobus);

    return 0;
    koltukSatis(otobus);
    FILE *fp;
    char str[60];
    fp = fopen("otobus.txt", "r");
    int sayac = 0;
    while (sayac!=41) {
    if (fp == NULL) {
        perror("Error opening file");
        return (-1);
    }
    if (fgets(str, 60, fp) != NULL) {
        puts(str);
    }
        sayac++;
}
    fclose(fp);
}



