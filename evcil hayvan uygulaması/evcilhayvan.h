#ifndef EVCIHAYVAN_H
#define EVCIHAYVAN_H

struct EvcilHayvan {
    char tur[20];
    char adi[20];
    int enerjiSeviyesi;
    int mutlulukSeviyesi;
};

void evcilHayvanDurumuGoster(struct EvcilHayvan *hayvan, const char *dosyaAdi);
void evcilHayvaniEkle(struct EvcilHayvan *hayvanlar, int *hayvanSayisi);
void evcilHayvaniGuncelle(struct EvcilHayvan *hayvanlar, int hayvanSayisi);
void evcilHayvaniSil(struct EvcilHayvan *hayvanlar, int *hayvanSayisi);
void evcilHayvanBesle(struct EvcilHayvan *hayvan);
void evcilHayvanaSuVer(struct EvcilHayvan *hayvan);
void evcilHayvanOyunOynat(struct EvcilHayvan *hayvan);
void evcilHayvaniTemizle(struct EvcilHayvan *hayvan);
void evcilHayvaniSev(struct EvcilHayvan *hayvan);
void evcilHayvaniUyut(struct EvcilHayvan *hayvan);

#endif  // EVCIHAYVAN_H
