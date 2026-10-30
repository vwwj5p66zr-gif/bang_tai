#include <Arduino.h>
#include "canh_bao.h"

#define DEN_KHAY_1 23
#define DEN_KHAY_2 25
#define DEN_KHAY_3 26

const int chan_den[3] = {
    DEN_KHAY_1,
    DEN_KHAY_2,
    DEN_KHAY_3
};

void khoi_tao_canh_bao()
{
    for (int i = 0; i < 3; i++)
    {
        pinMode(chan_den[i], OUTPUT);
        digitalWrite(chan_den[i], LOW);
    }
}

void bao_khay_day(int so_khay)
{
    if (so_khay < 1 || so_khay > 3)
    {
        return;
    }

    digitalWrite(chan_den[so_khay - 1], HIGH);
}

void tat_bao_khay(int so_khay)
{
    if (so_khay < 1 || so_khay > 3)
    {
        return;
    }

    digitalWrite(chan_den[so_khay - 1], LOW);
}