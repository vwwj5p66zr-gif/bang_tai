
#include <Arduino.h>
#include "cam_bien_hong_ngoai.h"

// =====================================
// 1. KHAI BAO CHAN CAM BIEN
// =====================================

// Ba cam bien phia truoc servo
#define CHAN_CAM_BIEN_TRUOC_1  0
#define CHAN_CAM_BIEN_TRUOC_2  2
#define CHAN_CAM_BIEN_TRUOC_3  4

// Ba cam bien tai khay
#define CHAN_CAM_BIEN_KHAY_1   5
#define CHAN_CAM_BIEN_KHAY_2   15
#define CHAN_CAM_BIEN_KHAY_3   16

// HIGH = co vat, LOW = khong co vat
#define MUC_CO_VAT HIGH
#define MUC_KHONG_CO_VAT LOW

#define THOI_GIAN_KHAY_DAY 5000UL

const int CHAN_CAM_BIEN_TRUOC[3] =
{
    CHAN_CAM_BIEN_TRUOC_1,
    CHAN_CAM_BIEN_TRUOC_2,
    CHAN_CAM_BIEN_TRUOC_3
};

const int CHAN_CAM_BIEN_KHAY[3] =
{
    CHAN_CAM_BIEN_KHAY_1,
    CHAN_CAM_BIEN_KHAY_2,
    CHAN_CAM_BIEN_KHAY_3
};

// =====================================
// 2. BIEN TRANG THAI
// =====================================

// Luu muc tin hieu lan doc truoc
int muc_truoc_cu[3];
int muc_khay_cu[3];

// Co san pham den truoc servo hay khong
bool co_san_pham_truoc_servo[3] =
{
    false, false, false
};

// Trang thai khay day
bool trang_thai_khay_day[3] =
{
    false, false, false
};

// Thoi gian phat hien khay day
unsigned long thoi_diem_bat_dau_day[3] =
{
    0, 0, 0
};

bool dang_dem_thoi_gian_day[3] =
{
    false, false, false
};

// =====================================
// 3. KHOI TAO CAM BIEN
// =====================================

void khoi_tao_cam_bien_hong_ngoai()
{
    for (int i = 0; i < 3; i++)
    {
        pinMode(CHAN_CAM_BIEN_TRUOC[i], INPUT);
        pinMode(CHAN_CAM_BIEN_KHAY[i], INPUT);

        muc_truoc_cu[i] =
            digitalRead(CHAN_CAM_BIEN_TRUOC[i]);

        muc_khay_cu[i] =
            digitalRead(CHAN_CAM_BIEN_KHAY[i]);

        // Neu cam bien khay dang HIGH khi khoi dong
        if (muc_khay_cu[i] == MUC_CO_VAT)
        {
            thoi_diem_bat_dau_day[i] = millis();
            dang_dem_thoi_gian_day[i] = true;
        }
    }
}

// =====================================
// 4. CAP NHAT CAM BIEN
// Goi lien tuc trong loop()
// =====================================

void cap_nhat_cam_bien_hong_ngoai()
{
    for (int i = 0; i < 3; i++)
    {
        int muc_truoc_moi =
            digitalRead(CHAN_CAM_BIEN_TRUOC[i]);

        int muc_khay_moi =
            digitalRead(CHAN_CAM_BIEN_KHAY[i]);

        // ---------------------------------
        // CAM BIEN TRUOC SERVO
        // Phat hien canh LOW -> HIGH
        // ---------------------------------

        if (muc_truoc_cu[i] == MUC_KHONG_CO_VAT &&
            muc_truoc_moi == MUC_CO_VAT)
        {
            co_san_pham_truoc_servo[i] = true;
        }

        // ---------------------------------
        // CAM BIEN KHAY
        // Chi theo doi trang thai khay day
        // ---------------------------------

        if (muc_khay_moi == MUC_CO_VAT)
        {
            if (!dang_dem_thoi_gian_day[i])
            {
                thoi_diem_bat_dau_day[i] = millis();
                dang_dem_thoi_gian_day[i] = true;
            }

            if (millis() - thoi_diem_bat_dau_day[i]
                >= THOI_GIAN_KHAY_DAY)
            {
                trang_thai_khay_day[i] = true;
            }
        }
        else
        {
            dang_dem_thoi_gian_day[i] = false;
            trang_thai_khay_day[i] = false;
        }

        // Luu trang thai hien tai
        muc_truoc_cu[i] = muc_truoc_moi;
        muc_khay_cu[i] = muc_khay_moi;
    }
}

// =====================================
// 5. KIEM TRA SAN PHAM TRUOC SERVO
// =====================================

bool phat_hien_san_pham_truoc_servo(int so_servo)
{
    if (so_servo < 1 || so_servo > 3)
    {
        return false;
    }

    int vi_tri = so_servo - 1;

    if (co_san_pham_truoc_servo[vi_tri])
    {
        co_san_pham_truoc_servo[vi_tri] = false;
        return true;
    }

    return false;
}

// =====================================
// 6. KIEM TRA KHAY DAY
// =====================================

bool khay_da_day(int so_khay)
{
    if (so_khay < 1 || so_khay > 3)
    {
        return false;
    }

    return trang_thai_khay_day[so_khay - 1];
}
