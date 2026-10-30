#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "man_hinh_lcd.h"

#define DIA_CHI_LCD 0x27
#define SO_COT_LCD 16
#define SO_DONG_LCD 2
#define CHAN_SDA_LCD 32
#define CHAN_SCL_LCD 33

LiquidCrystal_I2C lcd(DIA_CHI_LCD, SO_COT_LCD, SO_DONG_LCD);

void khoi_tao_lcd() {
    Wire.begin(CHAN_SDA_LCD, CHAN_SCL_LCD);
    lcd.init();
    lcd.backlight();
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("BANG TAI PHAN LOAI");

    lcd.setCursor(0, 1);
    lcd.print("Dang khoi dong...");
}

void xoa_man_hinh_lcd() {
    lcd.clear();
}

void hien_thi_lcd(int cot, int dong, const char *noi_dung) {
    if (cot < 0 || cot >= SO_COT_LCD) return;
    if (dong < 0 || dong >= SO_DONG_LCD) return;
    if (noi_dung == nullptr) return;

    lcd.setCursor(cot, dong);
    lcd.print("                "); // Xoa dong cu
    lcd.setCursor(cot, dong);
    lcd.print(noi_dung);
}

void hien_thi_thong_ke(int tong, int dem_khay_1, int dem_khay_2, int dem_khay_3) {
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Tong san pham:");
    lcd.print(tong);

    lcd.setCursor(0, 1);
    lcd.print("K1:");
    lcd.print(dem_khay_1);
    lcd.print(" K2:");
    lcd.print(dem_khay_2);
    lcd.print(" K3:");
    lcd.print(dem_khay_3);
}