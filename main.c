#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

int main(void)
{
    //Durum degiskenleri
    int saglik = 100, enerji = 100, oksijen = 100;
    int su, yedekParca, modulHasari;
    int kilitMuhurlu = 0;          /* hava kilidi muhurlu mu (0/1) */
    int gun = 1, tur = 0;
    int firtinaTurSayisi;

    //Diger degiskenler
    char zorluk, komut;
    int gecerli, oyunDevam = 1, turSayilsin;
    int sonuc = 0;                 /* 0: kaybetti, 1: kazandi, 2: cikis */
    int zar, esik;
    int miktar, cift, artik;       /* O komutu */
    int parca, onarim, harcanan;   /* T komutu */
    int i, olay, katsayi, kayip;   /* K komutu */
    int hasarTur, canKaybi, oksijenKaybi;
    int deneme, sifre;             /* H komutu */
    char giris;
    int gunRapor, puan;

    srand((unsigned int)time(NULL));

    printf("=== MARS KOLONISI YASAM DESTEK SIMULATORU ===\n");

    // Zorluk
    do {
        gecerli = 1;
        printf("Zorluk secin (K: Kolay, N: Normal, Z: Zor): ");
        if (scanf(" %c", &zorluk) != 1) return 0;

        switch (zorluk) {
            case 'k': case 'K':
                su = 40; yedekParca = 5; modulHasari = 0; firtinaTurSayisi = 3;
                break;
            case 'n': case 'N':
                su = 25; yedekParca = 3; modulHasari = 10; firtinaTurSayisi = 5;
                break;
            case 'z': case 'Z':
                su = 15; yedekParca = 2; modulHasari = 20; firtinaTurSayisi = 7;
                break;
            default:
                gecerli = 0;
                su = yedekParca = modulHasari = firtinaTurSayisi = 0;
                printf("Gecersiz seviye! Tekrar deneyin.\n");
        }
    } while (!gecerli);

    printf("\nKomutlar: G(Kesif) O(Oksijen uret) T(Tamir) D(Durum) "
           "U(Uyu) K(Kum firtinasi) H(Hava kilidi) Q(Cikis)\n");

    // Oyun dongusu
    do {
        printf("\n[Gun %d | Tur %d] Komut: ", gun, tur);
        if (scanf(" %c", &komut) != 1) { sonuc = 2; break; }
        turSayilsin = 1;

        switch (komut) {

            /* fall-through: 'g' ve 'G' ayni islemi yapar */
            case 'g':
            case 'G':
                if (enerji < 15 || oksijen < 10) {
                    printf("Yetersiz enerji/oksijen! Kesif iptal edildi.\n");
                    turSayilsin = 0;
                    break;
                }
                enerji -= 15;
                oksijen -= 10;
                zar = rand() % 100;
                if (enerji > 40 && oksijen > 30) esik = 60; else esik = 40;

                if (zar < 10 || modulHasari > 70) {
                    saglik -= 15;
                    printf("Zar: %d / Esik: 10 -> YARALANDIN! (-15 saglik)\n", zar);
                } else if (zar < esik) {
                    if (zar % 2 == 0) {
                        su += 10;
                        printf("Zar: %d / Esik: %d -> BASARILI: su kaynagi bulundu (+10 su)\n", zar, esik);
                    } else {
                        yedekParca += 1;
                        printf("Zar: %d / Esik: %d -> BASARILI: yedek parca bulundu (+1 parca)\n", zar, esik);
                    }
                } else {
                    printf("Zar: %d / Esik: %d -> BASARISIZ: eli bos donduk.\n", zar, esik);
                }
                break;

            case 'o':
            case 'O':
                if (enerji < 10) {
                    printf("Yetersiz enerji! Oksijen uretimi iptal edildi.\n");
                    turSayilsin = 0;
                    break;
                }
                printf("Kac birim su harcanacak? (mevcut: %d): ", su);
                scanf("%d", &miktar);
                if (miktar <= 0 || miktar > su) {
                    printf("Gecersiz miktar! Islem iptal.\n");
                    turSayilsin = 0;
                    break;
                }
                artik = miktar % 2;          /* tek ise 1 birim artar */
                cift  = miktar - artik;      /* harcanacak cift miktar */
                su -= cift;                  /* artik su depoda kalir */
                oksijen += (cift / 2) * 3;   /* 2 su -> 3 oksijen */
                enerji -= 10;
                printf("%d su harcandi, %d oksijen uretildi, %d su depoda kaldi.\n",
                       cift, (cift / 2) * 3, artik);
                break;

            case 't':
            case 'T':
                if (yedekParca == 0) {
                    printf("Yedek parca yok, tamir yapilamaz!\n");
                    turSayilsin = 0;
                    break;
                }
                if (modulHasari == 0) {
                    printf("Modul saglam, tamire gerek yok.\n");
                    turSayilsin = 0;
                    break;
                }
                if (enerji < 10) {
                    printf("Yetersiz enerji! Tamir iptal edildi.\n");
                    turSayilsin = 0;
                    break;
                }
                if (modulHasari <= 30)      { parca = 1; onarim = 15; }
                else if (modulHasari <= 70) { parca = 2; onarim = 30; }
                else                        { parca = 3; onarim = 45; }

                if (yedekParca < parca) harcanan = yedekParca;
                else                    harcanan = parca;
                onarim = onarim * harcanan / parca;
                yedekParca -= harcanan;
                modulHasari -= onarim;
                enerji -= 10;
                printf("%d parca harcandi, hasar %d azaldi.\n", harcanan, onarim);
                break;

            case 'd':
            case 'D':
                turSayilsin = 0;   //Durum raporunun tur sayılması engellendi
                printf("\n--- DURUM RAPORU ---\n");
                printf("Saglik:%d Enerji:%d Oksijen:%d Su:%d Parca:%d Hasar:%d Kilit:%d\n",
                       saglik, enerji, oksijen, su, yedekParca, modulHasari, kilitMuhurlu);
                if (oksijen < 25)     printf("UYARI: Oksijen kritik!\n");
                if (saglik < 30)      printf("UYARI: Saglik kritik!\n");
                if (modulHasari > 70) printf("UYARI: Modul hasari kritik!\n");
                if (oksijen >= 25 && saglik >= 30 && modulHasari <= 70)
                    printf("TUM SISTEMLER NORMAL\n");
                break;

            case 'u':
            case 'U':
                enerji += 20;
                oksijen -= 5;
                if (oksijen >= 20) {
                    saglik += 10;
                    printf("Dinlendin: +20 enerji, +10 saglik, -5 oksijen.\n");
                } else {
                    printf("Oksijen 20'nin altinda, saglik artmadi! (+20 enerji, -5 oksijen)\n");
                }
                break;

            case 'k':
            case 'K':
                if (enerji < 20) {
                    printf("Yetersiz enerji! Firtina simulasyonu iptal edildi.\n");
                    turSayilsin = 0;
                    break;
                }
                enerji -= 20;
                hasarTur = 0; canKaybi = 0; oksijenKaybi = 0;
                printf("KUM FIRTINASI basladi (%d tur)!\n", firtinaTurSayisi);

                for (i = 1; i <= firtinaTurSayisi; i++) {
                    olay = rand() % 100;
                    if (i % 2 == 0) katsayi = 2;   /* cift turda iki kati */
                    else            katsayi = 1;

                    if (olay >= 25 && olay < 50 && kilitMuhurlu == 1) {
                        printf("Tur %d | Zar: %d -> Oksijen sizintisi, kilit muhurlu: atlandi.\n", i, olay);
                        continue;
                    }

                    if (olay < 25) {
                        kayip = 10 * katsayi;
                        saglik -= kayip; canKaybi += kayip; hasarTur++;
                        printf("Tur %d | Zar: %d / Esik: 25 -> CAN KAYBI (-%d saglik)\n", i, olay, kayip);
                    } else if (olay < 50) {
                        kayip = 10 * katsayi;
                        oksijen -= kayip; oksijenKaybi += kayip; hasarTur++;
                        printf("Tur %d | Zar: %d / Esik: 50 -> OKSIJEN SIZINTISI (-%d oksijen)\n", i, olay, kayip);
                    } else if (olay < 75) {
                        kayip = 8 * katsayi;
                        modulHasari += kayip; hasarTur++;
                        printf("Tur %d | Zar: %d / Esik: 75 -> MODUL HASARI (+%d hasar)\n", i, olay, kayip);
                    } else {
                        printf("Tur %d | Zar: %d / Esik: 75 -> Firtinadan zarar gormedik.\n", i, olay);
                    }

                    if (saglik < 0) saglik = 0;
                    if (saglik > 100) saglik = 100;
                    if (oksijen < 0) oksijen = 0;
                    if (oksijen > 100) oksijen = 100;
                    if (modulHasari < 0) modulHasari = 0;
                    if (modulHasari > 100) modulHasari = 100;

                    if (saglik <= 0 || oksijen <= 0) {
                        printf("Kritik seviye! Firtina aniden sonlandi.\n");
                        break;
                    }
                }
                printf("FIRTINA OZETI: %d turda hasar, toplam %d saglik ve %d oksijen kaybi.\n",
                       hasarTur, canKaybi, oksijenKaybi);
                break;

            case 'h':
            case 'H':
                if (kilitMuhurlu == 1) {
                    printf("Hava kilidi zaten muhurlu.\n");
                    turSayilsin = 0;
                    break;
                }
                if (enerji < 5) {
                    printf("Yetersiz enerji! Hava kilidi islemi iptal edildi.\n");
                    turSayilsin = 0;
                    break;
                }
                sifre = 'A' + (gun % 26);
                deneme = 0;
                giris = 0;
                printf("Sifre alfabede A harfinden %d harf ileridedir. (3 deneme hakkin var)\n", gun % 26);

                do {
                    printf("Sifre (A-Z): ");
                    scanf(" %c", &giris);
                    giris = toupper(giris);   /* kucuk harf de kabul */
                    deneme++;
                    if (giris != sifre) {
                        enerji -= 5;
                        if (giris < sifre) printf("Yanlis! Ileri git.\n");
                        else               printf("Yanlis! Geri git.\n");
                    }
                    if (enerji < 0) enerji = 0;
                } while (giris != sifre && deneme < 3);   /* tek mantiksal ifade */

                if (giris == sifre) {
                    kilitMuhurlu = 1;
                    printf("Dogru sifre! Hava kilidi muhurlendi.\n");
                } else {
                    modulHasari += 20;
                    printf("3 deneme basarisiz! Modul hasari +20.\n");
                }
                break;

            case 'q':
            case 'Q':
                sonuc = 2;
                oyunDevam = 0;
                turSayilsin = 0;
                printf("Oyundan cikiliyor...\n");
                break;

            default:
                printf("Tanimsiz komut! Tur harcanmadi.\n");
                turSayilsin = 0;
        }

        // Zaman akışı
        if (turSayilsin) {
            tur++;
            if (tur % 3 == 0) {            /* her 3 turda yeni gun */
                gun++;
                oksijen -= 8;
                if (modulHasari > 70) saglik -= 5;
                printf(">> Yeni gun basladi: Gun %d (oksijen -8)\n", gun);
                if (modulHasari > 70)
                    printf(">> Modul hasari yuksek: saglik -5\n");
            }
        }

        // Sınırlandırmalar
        if (saglik < 0) saglik = 0;
        if (saglik > 100) saglik = 100;
        if (enerji < 0) enerji = 0;
        if (enerji > 100) enerji = 100;
        if (oksijen < 0) oksijen = 0;
        if (oksijen > 100) oksijen = 100;
        if (modulHasari < 0) modulHasari = 0;
        if (modulHasari > 100) modulHasari = 100;

        // Oyun sonu
        if (oyunDevam) {
            if (saglik <= 0 || oksijen <= 0) {
                sonuc = 0;
                oyunDevam = 0;
            } else if (gun > 15) {
                sonuc = 1;
                oyunDevam = 0;
            }
        }
    } while (oyunDevam);

    // Rapor
    if (gun > 15) gunRapor = 15;
    else          gunRapor = gun;
    puan = (gunRapor * 100) + saglik + oksijen - modulHasari;

    printf("\n===== SONUC RAPORU =====\n");
    if (sonuc == 1)      printf("KAZANDIN! Kurtarma ekibi geldi.\n");
    else if (sonuc == 0) printf("KAYBETTIN! Saglik veya oksijen tukendi.\n");
    else                 printf("Oyundan cikildi.\n");
    printf("Hayatta kalinan gun: %d | Toplam tur: %d\n", gunRapor, tur);
    printf("Saglik:%d Enerji:%d Oksijen:%d Su:%d Parca:%d Hasar:%d\n",
           saglik, enerji, oksijen, su, yedekParca, modulHasari);
    printf("PUAN = (gun x 100) + saglik + oksijen - modulHasari = %d\n", puan);

    return 0;
}
