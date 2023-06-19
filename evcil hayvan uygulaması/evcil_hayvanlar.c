#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PETS 10
#define MAX_NAME_LENGTH 50

// Evcil Hayvan Yapýsý
typedef struct {
    char tur[MAX_NAME_LENGTH];
    char ad[MAX_NAME_LENGTH];
    int enerji;
    int mutluluk;
} EvcilHayvan;

// Evcil Hayvan Duygu Durumu
typedef struct {
    int enerji_seviyesi;
    int mutluluk_seviyesi;
    char emoji[MAX_NAME_LENGTH];
    char text[MAX_NAME_LENGTH];
} DuyguDurumu;

struct Duygu {
    int enerjiSeviyesi;
    int mutlulukSeviyesi;
    char emoji[10];
    char text[20];
};

struct Duygu duygular[5] = {
    {25, 50, ":)", "Mutlu"},
    {20, 20, ":(", "Üzgün"},
    {10, 10, ":’(", "Aðlýyor"},
    {5, 0, ":zz", "Uyuyor"},
    {20, 0, ":-o", "Aç"},
};

struct Duygu* belirleDuyguDurumu(int enerjiSeviyesi, int mutlulukSeviyesi) {
    int i;
    for (i = 0; i < 5; i++) {
        if (enerjiSeviyesi > duygular[i].enerjiSeviyesi && mutlulukSeviyesi > duygular[i].mutlulukSeviyesi) {
            return &duygular[i];
        }
    }
    return NULL;
}
// Dosyadan Evcil Hayvan Verilerini Oku
void dosyadanHayvanlariOku(EvcilHayvan hayvanlar[], int* hayvanSayisi) {
    FILE* dosya = fopen("evcil_veri.txt", "r");
    if (dosya == NULL) {
        printf("Dosya bulunamadi!\n");
        return;
    }

    *hayvanSayisi = 0;
    while (fscanf(dosya, "%[^,],%[^,],%d,%d\n", hayvanlar[*hayvanSayisi].tur, hayvanlar[*hayvanSayisi].ad,
                  &hayvanlar[*hayvanSayisi].enerji, &hayvanlar[*hayvanSayisi].mutluluk) == 4) {
        (*hayvanSayisi)++;
    }

    fclose(dosya);
}

// Evcil Hayvan Verilerini Dosyaya Kaydet
void hayvanlariDosyayaKaydet(EvcilHayvan hayvanlar[], int hayvanSayisi) {
    FILE* dosya = fopen("evcil_veri.txt", "w");
    if (dosya == NULL) {
        printf("Dosya bulunamadi!\n");
        return;
    }

    for (int i = 0; i < hayvanSayisi; i++) {
        fprintf(dosya, "%s,%s,%d,%d\n", hayvanlar[i].tur, hayvanlar[i].ad, hayvanlar[i].enerji, hayvanlar[i].mutluluk);
    }

    fclose(dosya);
}

// Evcil Hayvaný Ekrana Yazdýr
void hayvaniEkranaYazdir(EvcilHayvan* hayvan) {
    printf("Turu: %s\n", hayvan->tur);
    printf("Adi: %s\n", hayvan->ad);
    printf("Enerji: %d\n", hayvan->enerji);
    printf("Mutluluk: %d\n", hayvan->mutluluk);
}
void hayvaniGuncelle(EvcilHayvan* hayvan) {
    printf("Yeni adi girin: ");
    scanf("%s", hayvan->ad);
    printf("Hayvan basariyla guncellendi!\n");
}

// Evcil Hayvaný Sil
void hayvaniSil(EvcilHayvan hayvanlar[], int* hayvanSayisi, int hayvanIndex) {
    if (hayvanIndex < 0 || hayvanIndex >= *hayvanSayisi) {
        printf("Gecersiz hayvan numarasi!\n");
        return;
    }

    for (int i = hayvanIndex; i < *hayvanSayisi - 1; i++) {
        hayvanlar[i] = hayvanlar[i + 1];
    }

    (*hayvanSayisi)--;
    printf("Hayvan basariyla silindi!\n");
}

// ...
// Evcil Hayvaný Besle
void hayvaniBesle(EvcilHayvan* hayvan) {
    hayvan->enerji += 15;
    hayvan->mutluluk += 10;
    printf("%s adli hayvana yemek verildi!\n", hayvan->ad);
}

// Evcil Hayvaný Su Ver
void hayvaniSuVer(EvcilHayvan* hayvan) {
    hayvan->enerji += 5;
    hayvan->mutluluk += 5;
    printf("%s adli hayvana su verildi!\n", hayvan->ad);
}

// Evcil Hayvana Oyun Oynat
void hayvaniOyunOynat(EvcilHayvan* hayvan) {
    hayvan->enerji -= 15;
    hayvan->mutluluk += 15;
    printf("%s adli hayvana oyun oynatildi!\n", hayvan->ad);
}

// Evcil Hayvani Temizle
void hayvaniTemizle(EvcilHayvan* hayvan) {
    hayvan->enerji -= 10;
    hayvan->mutluluk -= 5;
    printf("%s adli hayvan temizlendi!\n", hayvan->ad);
}

// Evcil Hayvani Sev
void hayvaniSev(EvcilHayvan* hayvan) {
    hayvan->mutluluk += 5;
    printf("%s adli hayvana sevgi gosterildi!\n", hayvan->ad);
}

// Evcil Hayvani Uyut
void hayvaniUyut(EvcilHayvan* hayvan) {
    hayvan->enerji += 5;
    printf("%s adli hayvan uyutuldu!\n", hayvan->ad);
}

// Evcil Hayvana Odul Ver
void hayvaniOdulVer(EvcilHayvan* hayvan) {
    hayvan->mutluluk += 10;
    printf("%s adli hayvana odul verildi!\n", hayvan->ad);
}

int main() {
    FILE *dosya, *ciktiDosya;
    dosya = fopen("duygu.txt", "r");
    ciktiDosya = fopen("evcil_cikti.txt", "w");

    if (dosya == NULL) {
        printf("duygu.txt dosyasi acilamadi.");
        exit(1);
    }

    if (ciktiDosya == NULL) {
        printf("evcil_cikti.txt dosyasi acilamadi.");
        exit(1);
    }

    char satir[100];
    int satirSayisi = 0;

    while (fgets(satir, sizeof(satir), dosya) != NULL) {
        satirSayisi++;

        char *token;
        token = strtok(satir, ",");
        int duyguNo = atoi(token);

        token = strtok(NULL, ",");
        char duyguMetni[20];
        strcpy(duyguMetni, token);

        token = strtok(NULL, ",");
        char duyguEmoji[10];
        strcpy(duyguEmoji, token);

        token = strtok(NULL, ",");
        int enerjiSeviyesi = atoi(token);

        token = strtok(NULL, ",");
        int mutlulukSeviyesi = atoi(token);

        struct Duygu *duygu = belirleDuyguDurumu(enerjiSeviyesi, mutlulukSeviyesi);

        if (duygu != NULL) {
            printf("%s %s\n", duygu->emoji, duyguMetni);
            fprintf(ciktiDosya, "%d,%s,%s,%d,%d\n", duyguNo, duyguMetni, duyguEmoji, enerjiSeviyesi, mutlulukSeviyesi);
        }
    }

    fclose(dosya);
    fclose(ciktiDosya);
    
    
	EvcilHayvan hayvanlar[MAX_PETS];
    int hayvanSayisi = 0;

    dosyadanHayvanlariOku(hayvanlar, &hayvanSayisi);

    // Kullanýcý arayüzü ve iþlemleri burada gercekleþtirilebilir
    printf("Evcil Hayvan Oyununa Hos Geldiniz!\n");
    printf("1. Evcil Hayvan Ekle\n");
    printf("2. Evcil Hayvan Guncelle\n");
    printf("3. Evcil Hayvan Sil\n");
    printf("4. Evcil Hayvanlari Goruntule\n");
    printf("5. Evcil Hayvana Yemek Ver\n");
    printf("6. Evcil Hayvana Su Ver\n");
    printf("7. Evcil Hayvana Oyun Oynat\n");
    printf("8. Evcil Hayvani Temizle\n");
    printf("9. Evcil Hayvani Sev\n");
    printf("10. Evcil Hayvani Uyut\n");
    printf("11. Evcil Hayvana Odul Ver\n");
    
    printf("0. Cikis\n");

    int secim;
    do {
        printf("\nSeciminizi yapin (0-11): ");
        scanf("%d", &secim);

        switch (secim) {
            case 1: {
                if (hayvanSayisi >= MAX_PETS) {
                    printf("Maksimum evcil hayvan sayisina ulasildi!\n");
                } else {
                    EvcilHayvan yeniHayvan;
                    printf("Hayvan turunu girin: ");
                    scanf("%s", yeniHayvan.tur);
                    printf("Hayvan adini girin: ");
                    scanf("%s", yeniHayvan.ad);
                    yeniHayvan.enerji = 60;
                    yeniHayvan.mutluluk = 60;

                    hayvanlar[hayvanSayisi] = yeniHayvan;
                    hayvanSayisi++;

                    printf("Yeni evcil hayvan olusturuldu!\n");
                }
                break;
            }
            case 2: {
        int hayvanIndex;
        printf("Guncellenecek hayvanin numarasini girin: ");
        scanf("%d", &hayvanIndex);
        hayvanIndex--;  // Dizideki indeks 0'dan baþladýðý için 1 çýkarýyoruz

        if (hayvanIndex < 0 || hayvanIndex >= hayvanSayisi) {
            printf("Gecersiz hayvan numarasi!\n");
        } else {
            hayvaniGuncelle(&hayvanlar[hayvanIndex]);
        }
        break;
    }

		    case 3: {
		        int hayvanIndex;
		        printf("Silinecek hayvanin numarasini girin: ");
		        scanf("%d", &hayvanIndex);
		        hayvanIndex--;  // Dizideki indeks 0'dan baþladýðý için 1 çýkarýyoruz
		
		        hayvaniSil(hayvanlar, &hayvanSayisi, hayvanIndex);
		        break;
		    }
            case 4: {
                printf("Evcil Hayvanlar:\n");
                for (int i = 0; i < hayvanSayisi; i++) {
                    printf("%d. Hayvan\n", i + 1);
                    hayvaniEkranaYazdir(&hayvanlar[i]);
                    printf("\n");
                }
                break;
            }
            case 5: {
                int hayvanIndex;
                printf("Yemek verilecek hayvanin numarasini girin: ");
                scanf("%d", &hayvanIndex);
                hayvanIndex--;  // Dizideki indeks 0'dan baþladýðý icin 1 cýkarýyoruz

                if (hayvanIndex < 0 || hayvanIndex >= hayvanSayisi) {
                    printf("Gecersiz hayvan numarasi!\n");
                } else {
                    hayvaniBesle(&hayvanlar[hayvanIndex]);
                }
                break;
            }
            case 6: {
                int hayvanIndex;
                printf("Su verilecek hayvanin numarasini girin: ");
                scanf("%d", &hayvanIndex);
                hayvanIndex--;  // Dizideki indeks 0'dan baþladýðý icin 1 cýkarýyoruz

                if (hayvanIndex < 0 || hayvanIndex >= hayvanSayisi) {
                    printf("Gecersiz hayvan numarasi!\n");
                } else {
                    hayvaniSuVer(&hayvanlar[hayvanIndex]);
                }
                break;
            }
            case 7: {
                int hayvanIndex;
                printf("Oyun oynatilacak hayvanin numarasini girin: ");
                scanf("%d", &hayvanIndex);
                hayvanIndex--;  // Dizideki indeks 0'dan baþladýðý icin 1 cýkarýyoruz

                if (hayvanIndex < 0 || hayvanIndex >= hayvanSayisi) {
                    printf("Gecersiz hayvan numarasi!\n");
                } else {
                    hayvaniOyunOynat(&hayvanlar[hayvanIndex]);
                }
                break;
            }
            case 8: {
                int hayvanIndex;
                printf("Temizlenecek hayvanin numarasini girin: ");
                scanf("%d", &hayvanIndex);
                hayvanIndex--;  // Dizideki indeks 0'dan baþladýðý icin 1 cýkarýyoruz

                if (hayvanIndex < 0 || hayvanIndex >= hayvanSayisi) {
                    printf("Gecersiz hayvan numarasi!\n");
                } else {
                    hayvaniTemizle(&hayvanlar[hayvanIndex]);
                }
                break;
            }
            case 9: {
                int hayvanIndex;
                printf("Sevgi gosterilecek hayvanin numarasini girin: ");
                scanf("%d", &hayvanIndex);
                hayvanIndex--;  // Dizideki indeks 0'dan baþladýðý icin 1 cýkarýyoruz

                if (hayvanIndex < 0 || hayvanIndex >= hayvanSayisi) {
                    printf("Gecersiz hayvan numarasi!\n");
                } else {
                    hayvaniSev(&hayvanlar[hayvanIndex]);
                }
                break;
            }
            case 10: {
                int hayvanIndex;
                printf("Uyutulacak hayvanin numarasini girin: ");
                scanf("%d", &hayvanIndex);
                hayvanIndex--;  // Dizideki indeks 0'dan baþladýðý icin 1 cýkarýyoruz

                if (hayvanIndex < 0 || hayvanIndex >= hayvanSayisi) {
                    printf("Gecersiz hayvan numarasi!\n");
                } else {
                    hayvaniUyut(&hayvanlar[hayvanIndex]);
                }
                break;
            }
            case 11: {
                int hayvanIndex;
                printf("Odul verilecek hayvanin numarasini girin: ");
                scanf("%d", &hayvanIndex);
                hayvanIndex--;  // Dizideki indeks 0'dan baþladýðý icin 1 cýkarýyoruz

                if (hayvanIndex < 0 || hayvanIndex >= hayvanSayisi) {
                    printf("Gecersiz hayvan numarasi!\n");
                } else {
                    hayvaniOdulVer(&hayvanlar[hayvanIndex]);
                }
                break;
            }
            case 0: {
                printf("Cikis yapiliyor...\n");
                break;
            }
            default: {
                printf("Gecersiz bir secim yaptiniz!\n");
                break;
            }
        }

    } while (secim != 0);

    hayvanlariDosyayaKaydet(hayvanlar, hayvanSayisi);

    return 0;
}
