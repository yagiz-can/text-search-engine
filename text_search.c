#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define RENK_YAZI "\x1b[36m" // Cyan renkli metin
#define RENK_RESET "\x1b[0m" // Renk sıfırla

// Küçük harfe çevirme fonksiyonu
void kucuk_harf(char *str) {
  for (int i = 0; str[i]; i++) {
    str[i] = tolower(str[i]);
  }
}

int sinir_mi(char c) { return c == '\0' || !isalnum((unsigned char)c); }

int satiri_analiz_et(char *asl_satir, char *kop_satir, char *aranan, int mod,
                     int k_len) {
  int bulunan_adet = 0;
  char *p = kop_satir;

  while ((p = strstr(p, aranan)) != NULL) {
    if (mod == 3) {
      int oncesi_tam = (p == kop_satir) || sinir_mi(*(p - 1));
      int sonrasi_tam = sinir_mi(*(p + k_len));
      if (oncesi_tam && sonrasi_tam)
        bulunan_adet++;
    } else {
      bulunan_adet++;
    }
    p++;
  }
  return bulunan_adet;
}

// Kelime arama fonksiyonu
int kelime_bulma(char dosya_adi[100], char kelime[100], int hassasiyet,
                 FILE *rapor) {
  char satir[1000], satir_kopya[1000], kelime_kopya[100];
  int kelime_sayac = 0, satir_sayac = 1;

  FILE *dosya = fopen(dosya_adi, "r");
  if (dosya == NULL) {
    printf("Hata: %s dosyasi acilamadi.\n", dosya_adi);
    fprintf(rapor, "Hata: %s dosyasi acilamadi.\n", dosya_adi);
    return -1;
  }

  fprintf(rapor, "\n~~~DOSYA ADI: %s~~~\n", dosya_adi);
  clock_t basla = clock();

  strcpy(kelime_kopya, kelime);
  if (hassasiyet >= 2)
    kucuk_harf(kelime_kopya);
  int k_len = strlen(kelime_kopya);

  printf("\n" RENK_YAZI "Arama basladi...\n" RENK_RESET);

  while (fgets(satir, sizeof(satir), dosya) != NULL) {
    char *ptr;
    strcpy(satir_kopya, satir);

    if (hassasiyet >= 2)
      kucuk_harf(satir_kopya);

    int bulunan =
        satiri_analiz_et(satir, satir_kopya, kelime_kopya, hassasiyet, k_len);

    if (bulunan > 0) {
      kelime_sayac += bulunan;
      printf(RENK_YAZI "Satir %d:" RENK_RESET " %s", satir_sayac, satir);
      fprintf(rapor, "Satir %d: %s", satir_sayac, satir);
    }
    satir_sayac++;
  }

  clock_t bitir = clock();
  double sure_ms = (double)(bitir - basla) * 1000 / CLOCKS_PER_SEC;

  printf("\n" RENK_YAZI "Arama tamamlandi! \n" RENK_RESET);
  printf("\nToplam %d adet '%s' kelimesi bulundu.\n", kelime_sayac,
         kelime_kopya);
  printf("Arama suresi: %.2f ms\n", sure_ms);
  fprintf(rapor, "Toplam %d adet bulundu. Islem suresi: %.2f ms\n",
          kelime_sayac, sure_ms);

  fclose(dosya);
  return kelime_sayac;
}

int main() {
  char kelime1[100], dosya_adi1[100];
  int secim, toplam_dosya = 0, genel_toplam_eslesme = 0;

  FILE *rapor_dosyasi = fopen("arama_raporu.txt", "w");
  if (rapor_dosyasi == NULL) {
    printf("Rapor dosyasi olusturulamadi!\n");
    return 1;
  }

  printf(RENK_YAZI
         "\n~~~~~~~~~~~~ KELIME ARAMA PROGRAMI ~~~~~~~~~~~~\n" RENK_RESET);

  printf("Aratmak istediginiz kelimeyi giriniz: ");
  fgets(kelime1, 100, stdin);
  kelime1[strcspn(kelime1, "\r\n")] = 0;

  printf("\nArama tipi seciniz:\n1: Duyarli\n2: Duyarsiz\n3: Tam Kelime "
         "(Duyarsiz)\nSecim: ");
  if (scanf("%d", &secim) != 1)
    return 1;
  getchar();

  while (1) {
    printf("\nTaranacak dosya adi (Cikis icin 'exit' yazin): ");
    fgets(dosya_adi1, sizeof(dosya_adi1), stdin);
    dosya_adi1[strcspn(dosya_adi1, "\r\n")] = 0;

    if (strcmp(dosya_adi1, "exit") == 0)
      break;

    int bulunan = kelime_bulma(dosya_adi1, kelime1, secim, rapor_dosyasi);

    if (bulunan != -1) {
      toplam_dosya++;
      genel_toplam_eslesme += bulunan;
    }
  }

  fprintf(rapor_dosyasi, "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  fprintf(rapor_dosyasi, "\n           GENEL ARAMA OZETI            ");
  fprintf(rapor_dosyasi, "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  fprintf(rapor_dosyasi, "\nAranan Kelime:   %s", kelime1);
  fprintf(rapor_dosyasi, "\nArama Modu:      %d", secim);
  fprintf(rapor_dosyasi, "\nTaranan Dosya:   %d", toplam_dosya);
  fprintf(rapor_dosyasi, "\nToplam Sonuc:    %d", genel_toplam_eslesme);
  fprintf(rapor_dosyasi, "\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");

  fprintf(rapor_dosyasi, "\n--- Arama oturumu sonlandirildi ---");
  fclose(rapor_dosyasi);

  printf("\nTum sonuclar 'arama_raporu.txt' dosyasina kaydedildi.\n");
  return 0;
}
