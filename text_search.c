#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int kelime_bulma(char dosya_adi[100], char kelime[100]) {

    char satir[1000];
    int kelime_sayac=0;
    int satir_sayac=1;

    FILE *dosya = fopen(dosya_adi,"r");
    if (dosya == NULL)
    {
        printf("Dosya acilamadi.\n");
        return 1;
    }

    while (fgets(satir,sizeof(satir),dosya) != NULL) 
    {
        char *ptr = satir;
        while ((ptr = strstr(ptr, kelime)) != NULL)
        {
            kelime_sayac++;
            printf("Kelime bulundu: %s (Satir %d)\n", kelime, satir_sayac);
            ptr += strlen(kelime); 
           
        }
        satir_sayac++;
    }

    printf("Toplam %d adet '%s' kelimesi bulundu.\n", kelime_sayac, kelime);
    fclose(dosya);
    return 0;
}

int main() {

    char kelime1[100];
    char dosya_adi1[100];


    printf("arama yapilacak dosyasinin icerigi girin:\n");
    fgets(dosya_adi1,sizeof(dosya_adi1),stdin);
    dosya_adi1[strcspn(dosya_adi1, "\r\n")] = 0; 
 
    printf("aratmak istediginiz kelimeyi girin: ");
    fgets(kelime1,100,stdin);
    kelime1[strcspn(kelime1, "\r\n")] = 0; 
    
    kelime_bulma(dosya_adi1,kelime1);

    
    return 0;
}

