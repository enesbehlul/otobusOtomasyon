#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef enum cinsiyet{E,K}cinsiyet;

typedef enum Dolu{D,B}Dolu;

typedef enum Gun{pazartesi,sali,carsamba,persembe,cuma,cumartesi,pazar}Gun;

typedef struct Musteri{
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

typedef struct Otobus{
    char plaka[9];
    char marka[15];
    int model;
    Koltuk koltuk[4][10];
    Gun gun;
}Otobus;

Musteri musteriOlustur(char adi[9],char soyadi[15],int tcNusu)
{
    Musteri mu;
    strcpy(mu.ad,adi);
    strcpy(mu.soyad,soyadi);
    mu.tcNu=tcNusu;
}

void koltukSatis()
{   char ad[9],soyad[15];
    int tcNu;
    puts("Müşterinin adını giriniz:");
    scanf("%s",ad);
    puts("Müşterinin soyadını giriniz:");
    scanf("%s",soyad);
    puts("Müşterinin kimlik numarasını giriniz:");
    scanf("%d",tcNu);
    musteriOlustur(ad,soyad,tcNu);
}

int main() {

    musteriOlustur("enes","yenidünya",1453);
    return 0;
}