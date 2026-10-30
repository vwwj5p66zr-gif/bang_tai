
#include <Arduino.h>

#include "cam_bien_hong_ngoai.h"
#include "servo_gat.h"

#define SO_SERVO 3
#define THOI_GIAN_GIU_SERVO 2000UL

bool servo_dang_hoat_dong[SO_SERVO] = {
    false, false, false
};

unsigned long thoi_diem_bat_dau[SO_SERVO] = {
    0, 0, 0
};

// =====================================
// XU LY KHI CAM BIEN PHAT HIEN VAT
// =====================================

void xu_ly_cam_bien(int so_servo)
{
    int vi_tri = so_servo - 1;

    // Neu servo dang quay thi khong kich hoat lai
    if (servo_dang_hoat_dong[vi_tri])
    {
        return;
    }

    // Kiem tra cam bien co phat hien vat khong
    if (phat_hien_san_pham_truoc_servo(so_servo))
    {
        Serial.print("Cam bien ");
        Serial.print(so_servo);
        Serial.println(" phat hien vat!");

        Serial.print("Servo ");
        Serial.print(so_servo);
        Serial.println(" quay 45 do");

        // Quay servo
        gat_san_pham(so_servo);

        servo_dang_hoat_dong[vi_tri] = true;

        thoi_diem_bat_dau[vi_tri] = millis();
    }
}

// =====================================
// TU DONG DUA SERVO VE 0 DO
// =====================================

void cap_nhat_servo()
{
    for (int i = 0; i < SO_SERVO; i++)
    {
        if (servo_dang_hoat_dong[i])
        {
            if (millis() - thoi_diem_bat_dau[i]
                >= THOI_GIAN_GIU_SERVO)
            {
                dua_servo_ve_ban_dau(i + 1);

                servo_dang_hoat_dong[i] = false;

                Serial.print("Servo ");
                Serial.print(i + 1);
                Serial.println(" tro ve 0 do");
            }
        }
    }
}

// =====================================
// SETUP
// =====================================

void setup()
{
    Serial.begin(115200);

    khoi_tao_cam_bien_hong_ngoai();

    khoi_tao_servo_gat();

    Serial.println("BAT DAU TEST CAM BIEN VA SERVO");
}

// =====================================
// LOOP
// =====================================

void loop()
{
    // Cap nhat du lieu cam bien
    cap_nhat_cam_bien_hong_ngoai();

    // Kiem tra tung cam bien
    xu_ly_cam_bien(1);

    xu_ly_cam_bien(2);

    xu_ly_cam_bien(3);

    // Cap nhat trang thai servo
    cap_nhat_servo();
}
