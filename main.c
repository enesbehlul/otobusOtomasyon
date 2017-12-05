#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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
    enum Dolu dolu;
    Musteri m1;
    Gun gun;
}Koltuk;

typedef struct Otobus
{
    char plaka[15];
    char marka[15];
    int model;
    Koltuk koltuk[4][10];
}Otobus;

Musteri musteriOlustur(char adi[9],char soyadi[15],int tcNusu)
{
    Musteri mu;
    strcpy(mu.ad,adi);
    strcpy(mu.soyad,soyadi);
    mu.tcNu=tcNusu;
    return mu;
}

void koltukSatis(Otobus otobus)
{

    char ad[9], soyad[15], gun[9];
    int tcNu, sutun, sira,sayi;
    puts("Musterinin adini giriniz:");
    scanf("%s",ad);
    puts("Musterinin soyadini giriniz:");
    scanf("%s",soyad);
    puts("Musterinin kimlik numarasini giriniz:");
    scanf("%d",&tcNu);
    puts("1 den 40 a koltuk numarasını giriniz:");
    scanf("%d",&sayi);
    sira = sayi/4;
    sutun = sayi%4;
    puts("haftanin gununugiriniz");
    scanf("%s",&otobus.koltuk[sutun][sira].gun);
    while(true){
        if(otobus.koltuk[sutun][sira].dolu==B)
        {
            otobus.koltuk[sutun][sira].m1=musteriOlustur(ad,soyad,tcNu);
            //memccpy(otobus.koltuk[sutun][sira].gun,gun,9,9);
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

void otobusDurumuGoster(){
    FILE *dosya;
    dosya = fopen("otobus.txt","r");

    fclose(dosya);
}



void anaEkran(Otobus otobus)
{
    puts("1- Otobus Durumunu Goster");
    puts("2- Koltuk Satıs");
    puts("3- Kisi Arama");
    puts("4- Cikis");
    int a;
    scanf("%d",&a);
    switch (a) {
        case 1:
            break;
        case 2:
            koltukSatis(otobus);
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            puts("yanlis giris yaptiniz");
    }
}
void koltuklariBosalt(Otobus *otobus)
{
    int i,j;
    for (i = 0; i <4 ; ++i) {
        for (j = 0; j <10 ; ++j) {
            otobus->koltuk[i][j].dolu=B;
        }
    }
}

void gunleriSifirla(Otobus *otobus){
    int i,j;
    for (i = 0; i <4 ; ++i) {
        for (j = 0; j <10 ; ++j) {
            otobus->koltuk[i][j].gun=pazartesi;
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
        fprintf(dosya,"%s/%s/%d\n",otobus.plaka,otobus.marka,otobus.model);
        fclose(dosya);
    }
}
void koltukDurumuYaz(Otobus *otobus){
    FILE *dosya;
    int i = 0,j,sayac=1;
    dosya = fopen("otobus.txt","a");
    koltuklariBosalt(otobus);
    for (i = 0;  i<4 ; i++) {
        for (j = 0; j <10 ; j++) {
            if(otobus->koltuk[i][j].dolu==1 && otobus->koltuk[i][j].m1.tcNu!=0 && otobus->koltuk[i][j].m1.cins!=0){
                fprintf(dosya,"%d/B/%d/%s/%s/%d/%d\n",sayac,otobus->koltuk[i][j].gun,otobus->koltuk[i][j].m1.ad,otobus->koltuk[i][j].m1.soyad,otobus->koltuk[i][j].m1.tcNu,otobus->koltuk[i][j].m1.cins);
            }
            else{
                fprintf(dosya,"%d/D/%d/%s/%s/%d/%d\n",sayac,otobus->koltuk[i][j].gun,otobus->koltuk[i][j].m1.ad,otobus->koltuk[i][j].m1.soyad,otobus->koltuk[i][j].m1.tcNu,otobus->koltuk[i][j].m1.cins);
            }
             sayac++;
        }
    }
    fclose(dosya);
}
void nullDegerAtama(Otobus *otobus){
    int i = 0,j,sayac=1;
    for (i = 0;  i<4 ; i++) {
        for (j = 0; j <10 ; j++) {
            otobus->koltuk[i][j].m1.cins=0;
            otobus->koltuk[i][j].m1.tcNu=0;
            strcpy(otobus->koltuk[i][j].m1.ad,"");
            strcpy(otobus->koltuk[i][j].m1.soyad,"");
        }
    }
}
int main(void) {
    Otobus *otobus = malloc(sizeof(*otobus));
    //strcpy(otobus->plaka, "34 MR 324");
    otobus->model = 403;
    strcpy(otobus->marka, "MERCEDES");
    nullDegerAtama(otobus);
    koltuklariBosalt(otobus);
    gunleriSifirla(otobus);
    koltukDurumuYaz(otobus);
    //anaEkran();
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

