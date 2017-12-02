#include <stdio.h>
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
    return mu;
}

void koltukSatis()
{
    char ad[9], soyad[15], gun[9];
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

}

void anaEkran()
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
            koltukSatis();
            break;
        case 3:
            break;
        case 4:
            break;
        default:
            puts("yanlis giris yaptiniz");
    }
}
void koltuklariBosalt()
{
    int i,j;
    for (i = 0; i <4 ; ++i) {
        for (j = 0; j <10 ; ++j) {
            otobus.koltuk[i][j].dolu=B;
        }
    }
}
int main(void)
{
    anaEkran();
}