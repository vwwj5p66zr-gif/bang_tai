#include <Arduino.h>
#include "cam_bien_mau.h"

#define CHAN_S0 17
#define CHAN_S1 18
#define CHAN_S2 19
#define CHAN_S3 21
#define CHAN_OUT 22

#define THOI_GIAN_DO_US 100000UL

void chon_bo_loc_mau(bool s2, bool s3) {
    digitalWrite(CHAN_S2, s2);
    digitalWrite(CHAN_S3, s3);
}

unsigned long doc_tan_so_mau(bool s2, bool s3) {
    chon_bo_loc_mau(s2, s3);

    delay(5);

    unsigned long thoi_gian = pulseIn(
        CHAN_OUT,
        LOW,
        THOI_GIAN_DO_US
    );

    if (thoi_gian == 0) {
        return 0;
    }

    return 1000000UL / thoi_gian;
}

void khoi_tao_cam_bien_mau() {
    pinMode(CHAN_S0, OUTPUT);
    pinMode(CHAN_S1, OUTPUT);
    pinMode(CHAN_S2, OUTPUT);
    pinMode(CHAN_S3, OUTPUT);
    pinMode(CHAN_OUT, INPUT);

    // Chon muc tan so dau ra 20%
    digitalWrite(CHAN_S0, HIGH);
    digitalWrite(CHAN_S1, LOW);
}

MauSanPham doc_mau_san_pham() {
    unsigned long do_do = doc_tan_so_mau(LOW, LOW);
    unsigned long do_vang = doc_tan_so_mau(HIGH, HIGH);
    unsigned long do_xanh_duong = doc_tan_so_mau(LOW, HIGH);

    if (do_do == 0 || do_vang == 0 || do_xanh_duong == 0) {
        return KHONG_XAC_DINH;
    }

    if (do_do >= 5200 && do_do <= 5800 &&
        do_vang >= 5600 && do_vang <= 6300 &&
        do_xanh_duong >= 7600 && do_xanh_duong <= 8600) {
        return KHONG_XAC_DINH;
    }

    if (do_vang < 4500 && do_xanh_duong < 6500) {
        return DO;
    }

    if (do_do > 11000 && do_vang > 9000 && do_xanh_duong < 9000) {
        return VANG;
    }

    if (do_do < 5000 && do_vang > 6000 && do_xanh_duong > 12000) {
        return XANH_DUONG;
    }

    return KHONG_XAC_DINH;
}
const char* ten_mau_san_pham(MauSanPham mau) {
    switch (mau) {
        case DO:
            return "DO";

        case VANG:
            return "VANG";

        case XANH_DUONG:
            return "XANH DUONG";

        default:
            return "KHONG RO";
    }
}
// Doc gia tri tan so cua tung kenh mau
void doc_du_lieu_mau(
    unsigned long &do_do,
    unsigned long &do_vang,
    unsigned long &do_xanh_duong
) {
    do_do = doc_tan_so_mau(LOW, LOW);
    do_vang = doc_tan_so_mau(HIGH, HIGH);
    do_xanh_duong = doc_tan_so_mau(LOW, HIGH);
}