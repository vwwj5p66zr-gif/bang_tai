#include <Arduino.h>
#include "dieu_khien_nut.h"

#define CHAN_NUT_RESET 27

#define THOI_GIAN_CHONG_DOI 50

bool trang_thai_nut_cu = HIGH;
bool trang_thai_nut = HIGH;

unsigned long thoi_gian_doi = 0;

bool co_yeu_cau_reset = false;

void khoi_tao_nut_nhan()
{
    pinMode(CHAN_NUT_RESET, INPUT_PULLUP);
}

void cap_nhat_nut_nhan()
{
    bool trang_thai_doc = digitalRead(CHAN_NUT_RESET);

    if (trang_thai_doc != trang_thai_nut_cu)
    {
        thoi_gian_doi = millis();
    }

    if (millis() - thoi_gian_doi > THOI_GIAN_CHONG_DOI)
    {
        if (trang_thai_doc != trang_thai_nut)
        {
            trang_thai_nut = trang_thai_doc;

            // INPUT_PULLUP: nhấn nút thì mức LOW
            if (trang_thai_nut == LOW)
            {
                co_yeu_cau_reset = true;
            }
        }
    }

    trang_thai_nut_cu = trang_thai_doc;
}

bool yeu_cau_reset_so_luong()
{
    if (co_yeu_cau_reset)
    {
        co_yeu_cau_reset = false;
        return true;
    }

    return false;
}