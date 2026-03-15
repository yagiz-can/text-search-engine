#include <stdio.h>
#include <string.h>

int main()
{
    FILE *dosya;
    char satir[256], kelime[50];
    int satirNo = 0, toplam = 0;

    printf("Dosya adi: ");
    scanf("%49s", kelime);  // burada kullanıcı dosya adını yazacak
    dosya = fopen(kelime, "r");
    if(dosya == NULL)
    {
        printf("Dosya acilamadi\n");
        return 1;
    }

    printf("Aranacak kelime: ");
    scanf("%49s", kelime);

    while(fgets(satir, sizeof(satir), dosya))
    {
        satirNo++;
        if(strstr(satir, kelime) != NULL)  // satırda kelime var mı
        {
            printf("Kelime %d. satirda bulundu\n", satirNo);
            toplam++;
        }
    }

    printf("\nToplam tekrar: %d\n", toplam);
    fclose(dosya);
    return 0;
}