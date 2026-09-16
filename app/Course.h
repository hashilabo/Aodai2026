/**
 * Course.h
 */
#ifndef ETTR_APP_COURSE_H_
#define ETTR_APP_COURSE_H_

#include <kernel.h>
#include "Section.h"

class Course {
public:
    explicit Course(Section* section);

    void add(Section* section);     // 区間を追加する
    Section* top() const;           // 先頭区間を返す
    Section* current() const;       // 現在の区間を返す
    Section* next();                // 次の区間を返す
    float currentMileage() const;   // 現区間の走行距離を返す
    float currentHeading() const;   // 現区間の進行方向を返す
    float currentKp() const;        // 比例ゲインを返す
    float currentKi() const;        // 積分ゲインを返す
    float currentKd() const;        // 微分ゲインを返す


private:
    Section* mTopSection;           // 先頭の区間
    Section* mCurrentSection;       // 現在の区間

};

#endif // ETTR_APP_COURSE_H_
