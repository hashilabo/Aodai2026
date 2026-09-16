/**
 * Section.h
 */
#ifndef ETTR_APP_SECTION_H_
#define ETTR_APP_SECTION_H_

struct Section {
    float mileage;      // 区間の走行距離[m]
    float heading;      // 区間終了時の進行方向(0-360)
    int pwm;            // 区間のpwm値
    float Kp;           // 比例ゲイン
    float Ki;           // 積分ゲイン
    float Kd;           // 微分ゲイン
    Section* next;      // 次の区間
};

#endif // ETTR_APP_SECTION_H_
