/**
 * OdoMeter.h
 */
#ifndef ETTR_APP_ODOMETER_H_
#define ETTR_APP_ODOMETER_H_

#include "Motor.h"

#define PI (3.14159265358979323846)

class OdoMeter {

public:
    static constexpr float TIRE_DIAMETER = 0.090f;   // タイヤ直径 0.09[m]

    OdoMeter(spikeapi::Motor &leftEncoder, spikeapi::Motor &rightEncoder);

    float getMileage();             // 総走行距離を取得する
    void setMileage(float mileage); // 指定走行距離を設定する
    void start();                   // 計測開始する
    void stop();                    // 計測終了する
    bool isMileageReached();        // 指定走行距離に達したかどうか
    bool isStarted();               // 計測開始したかどうか

private:

    spikeapi::Motor &mLeftEncoder;      // 関連端名 mLeftEncoder
    spikeapi::Motor &mRightEncoder;     // 関連端名 mRightEncoder
    
    float mDelayMileage;    // ディレイ走行距離(スタートから開始走行距離前までの距離)
    float mStartMileage;    // 開始走行距離(指定する走行距離)
    float mTargetMileage;   // ターゲット走行距離( = ディレイ走行距離 + 開始走行距離)

    int32_t getLeftCount();   // 左モーター角度を取得する
    int32_t getRightCount();  // 右モーター角度を取得する

};

#endif // ETTR_APP_ODOMETER_H_
