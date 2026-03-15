#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<ctype.h>

#define RENK_YAZI "\x1b[36m"   // Cyan renkli metin
#define RENK_RESET "\x1b[0m"   // Renk sıfırla

// Küçük harfe çevirme fonksiyonu
void kucuk_harf(char *str){
    for(int i=0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
}

//Kelime arama fonksiyonu
int kelime_bulma(char dosya_adi[100], char kelime[100], int hassasiyet) {
    char satir[1000];
    char satir_kopya[1000];
    char kelime_kopya[100];
    int kelime_sayac=0;
    int satir_sayac=1;

    FILE *dosya = fopen(dosya_adi,"r");
    if (dosya == NULL)
    {
        printf("Hata: Dosya acilamadi.\n" RENK_RESET);
        return 1;
    }

    clock_t basla = clock();
    strcpy(kelime_kopya, kelime);

    if(hassasiyet == 2){
        kucuk_harf(kelime_kopya); // harf duyarsız arama için küçük harfe çevir
    }

    printf("\n" RENK_YAZI "Arama basladi...\n" RENK_RESET);

    while (fgets(satir,sizeof(satir),dosya) != NULL) 
    {
        char *ptr;
        if(hassasiyet == 2){
            strcpy(satir_kopya, satir);
            kucuk_harf(satir_kopya);
            ptr = satir_kopya;
        } else {
            ptr = satir;
        }

        if(strstr(ptr, kelime_kopya) != NULL){
            printf(RENK_YAZI "Satir %d:" RENK_RESET " %s", satir_sayac, satir); 
            kelime_sayac++; 
           
        }

        satir_sayac++;
    }

    clock_t bitir = clock();
    double sure_ms = (double)(bitir - basla) * 1000 / CLOCKS_PER_SEC;

    printf("\n" RENK_YAZI "Arama tamamlandi! \n" RENK_RESET);
    printf("\nToplam %d adet '%s' kelimesi bulundu.\n", kelime_sayac, kelime);
    printf("Arama suresi: %.2f ms\n", sure_ms);

    fclose(dosya);
    return 0;
}

int main() {
    char kelime1[100];
    char dosya_adi1[100];
    int secim;

    printf(RENK_YAZI "\n======= KELIME ARAMA PROGRAMI =======\n" RENK_RESET);

    printf("Arama yapilacak dosyanin adini giriniz:\n");
    fgets(dosya_adi1,sizeof(dosya_adi1),stdin);
    dosya_adi1[strcspn(dosya_adi1, "\r\n")] = 0; 
 
    printf("Aratmak istediginiz kelimeyi giriniz: ");
    fgets(kelime1,100,stdin);
    kelime1[strcspn(kelime1, "\r\n")] = 0;
    
     printf("\nArama tipi seciniz:\n");
    printf("1 - Buyuk/kucuk harf DUYARLI\n");
    printf("2 - Buyuk/kucuk harf DUYARSIZ\n");
    printf("Seciminiz: ");
    scanf("%d",&secim);
    
    kelime_bulma(dosya_adi1, kelime1, secim);

    printf(RENK_YAZI "====================================\n" RENK_RESET);

    return 0;
}

