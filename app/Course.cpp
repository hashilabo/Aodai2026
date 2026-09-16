/**
 * Course.cpp
 */
#include "Course.h"

/**
 * コンストラクタ
 * @param section 先頭の区間
 */
Course::Course(Section* section)
    : mTopSection(section),
      mCurrentSection(section) {
    }

/**
 * 区間を追加する
 * @param section 追加する区間
 */
void Course::add(Section* section) {
    if (mTopSection == 0) {         // 先頭の区間が設定されてない場合
        mTopSection = section;      // 先頭の区間を設定する
    } else {                        // それ以外の場合（先頭の区間が設定している場合）
        Section* s = mTopSection;   // 変数sに先頭の区間を設定する
        while (s->next != top()) {  // 次の区間が先頭の区間でなくなるまで繰り返す
            s = s->next;            // 変数に次の区間を設定
        }
        s->next = section;          // 次の区間に追加する区間を設定する
    }
    section->next = top();          // その次の区間に先頭区間を設定する

}

/**
 * 先頭区間を返す
 * @return 先頭区間
 */
Section* Course::top() const {
    return mTopSection;
}

/**
 * 現在の区間を返す
 * @return 現在の区間
 */
Section* Course::current() const {
    return mCurrentSection;
}

/**
 * 次の区間へ進める
 * @return 次の区間
 */
Section* Course::next() {
    if (mCurrentSection != 0) {                     // 現在の区間が0でない場合(ある場合)
        mCurrentSection = mCurrentSection->next;    // 現在の区間を次の区間に進める
    } else {                                        // それ以外の場合
        mCurrentSection = mTopSection;              // 現在の区間を先頭区間にする
    }
    return mCurrentSection;                         // 値を返す
}

/**
 * 現区間の走行距離を取得する
 * @return 現区間の走行距離[m]
 */
float Course::currentMileage() const {
    return (mCurrentSection == 0) ? 0 : mCurrentSection->mileage;
}

/**
 * 現区間の進行方向を取得する
 * @return 現区間の進行方向(0-360)
 */
float Course::currentHeading() const {
    return (mCurrentSection == 0) ? 0 : mCurrentSection->heading;
}

/**
 * 比例ゲインを取得する
 * @param 比例ゲイン
 */
float Course::currentKp() const {
    return (mCurrentSection == 0) ? 0 : mCurrentSection->Kp;
}

/**
 * 積分ゲインを取得する
 * @param 積分ゲイン
 */
float Course::currentKi() const {
    return (mCurrentSection == 0) ? 0 : mCurrentSection->Ki;
}

/**
 * 微分ゲインを取得する
 * @param 微分ゲイン
 */
float Course::currentKd() const {
    return (mCurrentSection == 0) ? 0 : mCurrentSection->Kd;
}
