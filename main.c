#include <stdio.h>

int main() {
    printf("Hello, World!\n");

    struct musteri{
        char ad[9];
        char soyad[15];
        int tcNu;
        enum cinsiyet{erkek,kadin}cinsiyet;
    };

    enum gun{pazartesi,sali,carsamba,persembe,cuma,cumartesi,pazar};

    struct koltuk{
        int nu;
        enum dolu{d,b};
    };
    struct otobus{
        char plaka[9];
        char marka[15];
        int model;

    };
    return 0;
}