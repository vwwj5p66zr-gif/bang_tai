#include <Arduino.h>
#include <ESP32Servo.h>
#include "servo_gat.h"

// Chan dieu khien 3 servo
#define CHAN_SERVO_1 12
#define CHAN_SERVO_2 13
#define CHAN_SERVO_3 14

// Goc hoat dong
#define GOC_BAN_DAU 0
#define GOC_GAT 45

#define SO_SERVO 3

const int chan_servo[SO_SERVO] = {
    CHAN_SERVO_1,
    CHAN_SERVO_2,
    CHAN_SERVO_3
};

Servo cac_servo[SO_SERVO];

void khoi_tao_servo_gat() {
    for (int i = 0; i < SO_SERVO; i++) {
        cac_servo[i].setPeriodHertz(50);
        cac_servo[i].attach(chan_servo[i], 500, 2400);
        cac_servo[i].write(GOC_BAN_DAU);
    }
}

void gat_san_pham(int so_servo) {
    if (so_servo < 1 || so_servo > SO_SERVO) {
        return;
    }

    cac_servo[so_servo - 1].write(GOC_GAT);
}

void dua_servo_ve_ban_dau(int so_servo) {
    if (so_servo < 1 || so_servo > SO_SERVO) {
        return;
    }

    cac_servo[so_servo - 1].write(GOC_BAN_DAU);
}