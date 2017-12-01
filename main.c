#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum cinsiyet{E,K}cinsiyet;

typedef enum Dolu{D,B}Dolu;

typedef enum Gun{pazartesi,sali,carsamba,persembe,cuma,cumartesi,pazar}Gun;

typedef struct Musteri
{
    char ad[9];
    char soyad[15];
    int tcNu;
    cinsiyet cins;
}Musteri;

typedef struct Koltuk{
    int nu;
    enum Dolu dolu;
    Musteri m1;
}Koltuk;

typedef struct Otobus
{
    char plaka[9];
    char marka[15];
    int model;
    Koltuk koltuk[4][10];
    Gun gun;
}Otobus;
    Otobus otobus;

Musteri musteriOlustur(char adi[9],char soyadi[15],int tcNusu)
{
    Musteri mu;
    strcpy(mu.ad,adi);
    strcpy(mu.soyad,soyadi);
    mu.tcNu=tcNusu;
}

void koltukSatis()
{   char ad[9], soyad[15];
    int tcNu, sutun, sira;
    puts("Musterinin adini giriniz:");
    scanf("%s",ad);
    puts("Musterinin soyadini giriniz:");
    scanf("%s",soyad);
    puts("Musterinin kimlik numarasini giriniz:");
    scanf("%d",&tcNu);
    puts("0 dan 9 a koltuk sirasini giriniz:");
    scanf("%d",&sira);
    puts("0 dan 3 e koltuk sutununu giriniz:");
    scanf("%d",&sutun);
    while(true){
        if(otobus.koltuk[sutun][sira].dolu==D)
        {
            otobus.koltuk[sutun][sira].m1=musteriOlustur(ad,soyad,tcNu);
            break;
        }
        else {
            puts("Bu koltuk dolu lütfen başka bir koltuk giriniz");
            puts("0 dan 9 a koltuk sırasını giriniz:");
            scanf("%d",&sira);
            puts("0 dan 3 e koltuk sutununu giriniz:");
            scanf("%d",&sutun);
        }
    }
}

int main(void)
{
    koltukSatis();
}