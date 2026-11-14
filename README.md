# marskolonioyunu
# Mars Kolonisi Yaşam Destek Simülatörü

Bu proje C dili ile yazdığım bir konsol oyunudur. Oyunda Mars'taki bir kolonide hayatta kalmaya çalışıyoruz. Sağlık, enerji ve oksijen değerlerini yönetip 15 gün boyunca hayatta kalırsak oyunu kazanıyoruz.

## Derleme ve Çalıştırma

gcc main.c -o mars
./mars

Ek bir kütüphane gerekmiyor. Kodda stdio.h, stdlib.h, time.h ve ctype.h kullanıldı.

## Oyunun Amacı

Kazanmak için 15 günü tamamlamak gerekiyor. Sağlık veya oksijen 0 olursa oyunu kaybediyoruz. Q komutu ile de oyundan çıkılabiliyor.

## Zorluk Seviyeleri

Oyun başında zorluk seçiliyor. K kolay, N normal, Z zor demek (büyük küçük harf fark etmiyor). Geçersiz bir harf girilirse tekrar soruluyor.

Kolay: 40 su, 5 yedek parça, 0 modül hasarı, fırtına 3 tur
Normal: 25 su, 3 yedek parça, 10 modül hasarı, fırtına 5 tur
Zor: 15 su, 2 yedek parça, 20 modül hasarı, fırtına 7 tur

Her seviyede sağlık, enerji ve oksijen 100 ile başlıyor ve bu değerler 0 ile 100 arasında tutuluyor.

## Komutlar

G (Keşif): Enerji en az 15, oksijen en az 10 olmalı. 15 enerji ve 10 oksijen harcanıyor. 0 ile 99 arasında bir zar atılıyor. Zar 10'dan küçükse veya modül hasarı 70'ten büyükse yaralanıyoruz ve 15 sağlık kaybediyoruz. Zar eşikten küçükse çift sayıda 10 su, tek sayıda 1 yedek parça buluyoruz. Eşik, enerji 40'tan ve oksijen 30'dan büyükse 60, değilse 40 oluyor.

O (Oksijen üret): En az 10 enerji gerekiyor ve 10 enerji harcanıyor. Kullanıcıdan kaç su harcanacağı soruluyor. 2 su 3 oksijen üretiyor. Tek sayı girilirse artan 1 su depoda kalıyor.

T (Tamir): Yedek parça olmalı, modül hasarı 0'dan büyük olmalı ve en az 10 enerji olmalı. Hasar 30 veya altındaysa 1 parça ile 15, 70 veya altındaysa 2 parça ile 30, daha fazlaysa 3 parça ile 45 hasar onarılıyor. Parça yetmezse onarım parça oranına göre azalıyor. 10 enerji harcanıyor.

D (Durum): Tüm değerleri ve kritik uyarıları gösteriyor. Tur sayılmıyor.

U (Uyu): 20 enerji kazanılıyor, 5 oksijen harcanıyor. Oksijen 20 veya üstündeyse 10 sağlık da kazanılıyor.

K (Kum fırtınası): En az 20 enerji gerekiyor ve 20 enerji harcanıyor. Fırtına seçilen zorluktaki tur sayısı kadar sürüyor.

H (Hava kilidi): En az 5 enerji gerekiyor. Şifre mini oyunu oynanıyor. Kilit zaten mühürlüyse işlem yapılmıyor.

Q (Çıkış): Oyundan çıkıyor. Tur sayılmıyor.

Tanımsız komut girilirse veya enerji yetmediği için işlem iptal olursa tur harcanmıyor.

## Zaman Akışı

Tur sayılan her komut turu 1 artırıyor. Her 3 turda bir yeni gün başlıyor ve oksijen 8 azalıyor. Modül hasarı 70'ten büyükse sağlık da 5 azalıyor.

## Kum Fırtınası

Fırtınanın her turunda 0 ile 99 arasında bir zar atılıyor. Çift numaralı turlarda kayıplar 2 katı oluyor.

0 ile 24 arası: can kaybı, 10 çarpı katsayı kadar sağlık gidiyor
25 ile 49 arası: oksijen sızıntısı, 10 çarpı katsayı kadar oksijen gidiyor
50 ile 74 arası: modül hasarı, 8 çarpı katsayı kadar hasar artıyor
75 ile 99 arası: zarar yok

Hava kilidi mühürlüyse oksijen sızıntısı olayı atlanıyor. Sağlık veya oksijen 0 olursa fırtına yarıda bitiyor. Fırtına sonunda bir özet yazdırılıyor.

## Hava Kilidi Şifre Oyunu

Şifre, A harfinden (gün mod 26) kadar ileridedir. Örneğin 3. günde şifre D oluyor. 3 deneme hakkı var ve küçük harf de kabul ediliyor. Her yanlış denemede 5 enerji kaybediliyor ve ileri git veya geri git ipucu veriliyor. Şifre doğru bilinirse kilit mühürleniyor. 3 denemede de bilinemezse modül hasarı 20 artıyor.

## Puan Hesabı

Oyun bitince sonuç raporu yazdırılıyor. Puan şöyle hesaplanıyor:

puan = (gün x 100) + sağlık + oksijen - modül hasarı

Gün sayısı en fazla 15 alınıyor.

## Kodda Kullanılan Yapılar

- Zorluk seçimi için do-while döngüsü ve switch kullanıldı.
- Ana oyun döngüsü do-while ile yazıldı, komutlar switch ile işleniyor.
- Büyük ve küçük harf aynı işi yapsın diye case düşmesi (fall-through) kullanıldı.
- Fırtınada for döngüsü, continue ve break kullanıldı.
- Rastgele sayılar için srand ve rand kullanıldı.
- Her turdan sonra değerler 0 ile 100 arasına sınırlandırılıyor.
