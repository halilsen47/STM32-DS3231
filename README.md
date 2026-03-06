# 🕰️ STM32 & DS3231 Kesme Tabanlı Alarm Sistemi

Bu proje, **STM32F401 (Blackpill)** mikrodenetleyicisi ve **DS3231 RTC** modülü kullanılarak geliştirilmiş, düşük güç tüketimi ve hassas zamanlama odaklı bir alarm sistemidir. 

Sistem, işlemciyi sürekli meşgul etmek yerine (polling), DS3231'in donanımsal alarm sinyalini **EXTI (External Interrupt)** üzerinden yakalayarak çalışır.

---

## 🎯 Proje Amacı
İşlemci kaynaklarını verimli kullanarak, gerçek zamanlı saat verisi üzerinden hassas alarmlar oluşturmak ve bu alarmları donanımsal kesmelerle (interrupt) yönetmektir.

## ✨ Öne Çıkan Özellikler
* **Gerçek Zamanlı Saat:** DS3231 üzerinden yüksek doğrulukta tarih ve saat okuma/yazma.
* **Donanımsal Alarm 1:** Belirlenen saniye, dakika, saat veya gün değerine göre tetiklenme.
* **EXTI (Dış Kesme):** Alarm tetiklendiğinde DS3231'in `SQW/INT` pini üzerinden STM32'yi uyarma.
* **Modüler Mimari:** Sürücü dosyalarının (`.c` / `.h`) ana koddan bağımsız, taşınabilir yapısı.

---

## 🛠️ Donanım Gereksinimleri
* **MCU:** STM32F401CCU6 (Blackpill) veya muadili bir STM32 kartı.
* **RTC:** DS3231 Hassas RTC Modülü.
* **Direnç:** I2C hatları için STM32 dahili **Pull-up** dirençleri konfigüre edilmiştir.
* **Bağlantı:** Jumper kablolar.

---

## 🔌 Pinout (Bağlantı Şeması)

| DS3231 Pin | STM32 Pin | Fonksiyon | Açıklama |
| :--- | :--- | :--- | :--- |
| **VCC** | 3.3V | Güç Girişi | 3.3V Besleme |
| **GND** | GND | Toprak | Ortak Şase |
| **SDA** | PB9 | I2C Data | Veri Hattı |
| **SCL** | PB8 | I2C Clock | Saat Hattı |
| **SQW/INT** | PB1 | EXTI Line | Alarm Kesme Hattı |

---

## 📂 Yazılım Mimarisi

Proje dosyaları düzenli bir hiyerarşi ile ayrılmıştır:

* **`Core/Src/ds3231.c`**: RTC sürücü fonksiyonları, BCD-Decimal dönüşümleri ve I2C komutları.
* **`Core/Inc/ds3231.h`**: Register adresleri, kontrol bitleri ve veri yapısı tanımları.
* **`main.c`**: EXTI callback fonksiyonu (`HAL_GPIO_EXTI_Callback`) ve uygulama mantığı.

---

## 🚀 Hızlı Başlangıç

1.  **Depoyu Klonlayın:**
    ```bash
    git clone [https://github.com/halilsen47/STM32-DS3231.git](https://github.com/halilsen47/STM32-DS3231.git)
    ```
2.  **Projeyi Açın:** STM32CubeIDE üzerinden projeyi "Open Project from File System" seçeneği ile içe aktarın.
3.  **Ayarları Kontrol Edin:** `.ioc` dosyasında I2C1 ve PB1 pinlerinin doğru modda olduğundan emin olun.
4.  **Derle ve Yükle:** Kodu derleyip kartınıza yükledikten sonra terminal üzerinden alarm çıktılarını izleyebilirsiniz.

---

## 📝 Notlar
> [!IMPORTANT]
> DS3231'in `INT` pini "Active Low" (Lojik 0) çalışır. Bu nedenle STM32 tarafında EXTI pini **Falling Edge** (Düşen Kenar) ve **Pull Down** modunda ayarlanmalıdır.
---
