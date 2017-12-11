#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAXSATIR 10
#define MAXSUTUN 4

typedef enum cinsiyet{E,K}cinsiyet;
typedef enum Dolu{D,B}Dolu;
typedef enum Gun{pazartesi=1,sali,carsamba,persembe,cuma,cumartesi,pazar}Gun;

typedef struct Musteri {
    char ad[9];
    char soyad[15];
    int tcNu;
    cinsiyet cins;
}Musteri;

typedef struct Koltuk {
    int nu;
    Dolu dolu;
    Musteri m1;
    Gun gun;
}Koltuk;

typedef struct Otobus {
    char plaka[15];
    char marka[15];
    int model;
    Koltuk koltuk[MAXSATIR][MAXSUTUN];
}Otobus;

void koltukDurumunuDosyayaYaz(Otobus *);
void kisiArama(Otobus *);

void ekraniTemizle() {
    system("@cls||clear");
}

void koltukSatis(Otobus *otobus) {
    ekraniTemizle();
    char ad[9], soyad[15];
    int tcNu, sutun, sira,sayi,cinsiyet,gun;
    char *devamMi = malloc(2* sizeof(char));
    strcpy(devamMi,"y");
    while(!strcmp(devamMi,"y")){
        puts("Bilgileri giriniz...");
        printf("\nMusteri>\n\tAd: ");
        scanf("%s",ad);
        printf("\n\tSoyad: ");
        scanf("%s",soyad);
        printf("\n\tTC: ");
        scanf("%d",&tcNu);
        puts("Erkek icin 0, kadin icin 1");
        printf("\n\tCinsiyet: ");
        scanf("%d",&cinsiyet);
        printf("\nKoltuk>\n\tNU: ");
        scanf("%d",&sayi);
        printf("\n\tGun: ");
        scanf("%d",&gun);
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
                puts("*****SATIS ISLEMI TAMAMLANDI*****");
                puts("Yeni koltuk satin almak ister misiniz? y/n");
                scanf("%s",devamMi);
                koltukDurumunuDosyayaYaz(otobus);
                ekraniTemizle();
                break;
            }
            else {
                puts("Bu koltuk dolu lutfen baska bir koltuk giriniz");
                puts("1 den 40 a koltuk numarasini giriniz:");
                scanf("%d",&sayi);
                sira = (sayi-1)/MAXSUTUN;
                sutun = (sayi-1)%MAXSUTUN;
            }
        }
    }
}

void otobusDurumuGoster(Otobus *otobus){
    ekraniTemizle();
    int i,j;
    printf("%s %s %d\nS|\t1\t2\t3\t4\n\t-\t-\t-\t-\n",otobus->plaka,otobus->marka,otobus->model);
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

void anaEkran(Otobus *otobus) {
    while(1){
        puts("1- Otobus Durumunu Goster");
        puts("2- Koltuk Satis");
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
    fprintf(dosya,"%s %s %d\n",otobus->plaka,otobus->marka,otobus->model);
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
    strcpy(otobus->plaka, "34.MR.324");
    otobus->model = 403;

    Koltuk **koltuklar = (Koltuk **)malloc(MAXSATIR* sizeof(Koltuk *));

    for (i = 0; i < MAXSATIR; i++) {
        koltuklar[i]= (Koltuk *)malloc(MAXSUTUN* sizeof(Koltuk));
    }

    for (i = 0;  i<MAXSATIR ; i++) {
        for (j = 0; j <MAXSUTUN ; j++) {
            koltuklar[i][j].nu = sayac++;
            koltuklar[i][j].m1.cins=E;
            koltuklar[i][j].m1.tcNu=0;
            strcpy(koltuklar[i][j].m1.ad,"Bos");
            strcpy(koltuklar[i][j].m1.soyad,"Koltuk");
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
        char *dolu=malloc(sizeof(char));
        FILE *dosya;
        dosya = fopen("otobus.txt","r");

        fscanf(dosya,"%s %s %d\n",otobus->plaka,otobus->marka,&otobus->model);
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
    ekraniTemizle();
    bool a = false;
    int tcNu=5,i,j;
    int hafta;
    char *yN = malloc(2* sizeof(char));
    strcpy(yN,"y");
    while (!strcmp(yN,"y")){
        printf("\nTc giriniz.");
        scanf("%d",&tcNu);
        for (i = 0; i < MAXSATIR ; i++) {
            for (j = 0; j < MAXSUTUN ; j++) {
                if(otobus->koltuk[i][j].m1.tcNu==tcNu){
                    printf("\nMusteri>\n\tAd: %s\n\tSoyad: %s\n\tTc: %d",otobus->koltuk[i][j].m1.ad,otobus->koltuk[i][j].m1.soyad,otobus->koltuk[i][j].m1.tcNu);
                    printf("\nKoltuk>\n\tNu: %d\n\tGun: %d",otobus->koltuk[i][j].nu,otobus->koltuk[i][j].gun);
                    a=true;
                    break;
                }
            }
        }
        if(a == false)
            puts("BULUNAMADI");
        printf("\nYeni arama yapmak ister misiniz, y/n");
        scanf("%s",yN);
        ekraniTemizle();
    }
}

int main(void) {
    Otobus *otobus = (Otobus *)malloc(sizeof(Otobus));
    //bosOtobusStructiOlustur(otobus);
    dosyadanOtobusBilgileriOku(otobus);
    anaEkran(otobus);
    return 0;
}