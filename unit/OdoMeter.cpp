/**
 * OdoMeter.cpp
 */
#include "OdoMeter.h"

/**
 * コンストラクタ
 * @param 
 */
OdoMeter::OdoMeter(spikeapi::Motor &leftEncoder, spikeapi::Motor &rightEncoder)
    : mLeftEncoder(leftEncoder), 
      mRightEncoder(rightEncoder),
      mDelayMileage(0.0f),
      mStartMileage(0.0f),
      mTargetMileage(0.0f)
      {}

/**
 * 総走行距離を取得する
 */
float OdoMeter::getMileage() {
    return PI * OdoMeter::TIRE_DIAMETER * (getLeftCount() + getRightCount()) / 720.0f;
}

/**
 * 指定走行距離を設定する
 * @param mileage 指定走行距離
 */
void OdoMeter::setMileage(float mileage) {
    mDelayMileage = mileage;
}

/**
 * 計測開始する
 */
void OdoMeter::start() {
    mStartMileage = getMileage();
    mTargetMileage = mDelayMileage + mStartMileage;
}

/**
 * 計測終了する
 */
void OdoMeter::stop() {
    mStartMileage = 0.0f;
    mTargetMileage = 0.0f;
}

/**
 * 指定走行距離に達したかどうか
 * @retval true 指定走行距離に達した
 * @retval false 指定走行距離に達していない
 */
bool OdoMeter::isMileageReached() {
    return (getMileage() >= mTargetMileage) ? true : false;
}

/**
 * 計測開始したかどうか
 * @retval true 計測開始した
 * @retval false 計測開始していない
 */
bool OdoMeter::isStarted() {
    return (mStartMileage == 0.0f) ? false : true;
}

/**
 * 左モーター回転角度を取得する
 */
int32_t OdoMeter::getLeftCount() {
    return mLeftEncoder.getCount();
}

/**
 * 右モーター回転角度を取得する
 */
int32_t OdoMeter::getRightCount() {
    return mRightEncoder.getCount();
}
