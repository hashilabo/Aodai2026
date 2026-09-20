/**
 * ColorDetector.cpp
 */
#include "ColorDetector.h"
#include <cstdio>

/**
 * コンストラクタ
 * @param colorSensor ColorSensorの参照
 */
ColorDetector::ColorDetector(const spikeapi::ColorSensor& colorSensor)
    : mColorSensor(colorSensor) {
}

/**
 * HSV色情報を更新する
 */
void ColorDetector::update() {
    spikeapi::ColorSensor::HSV hsv;
    mColorSensor.getHSV(hsv);

    mHue = hsv.h;
    mSaturation = hsv.s;
    mValue = hsv.v;
}

/**
 * 色相（Hue）を取得する
 */
uint16_t ColorDetector::getHue() const {
    return mHue;
}

/**
 * 彩度（Saturation）を取得する
 */
uint8_t ColorDetector::getSaturation() const {
    return mSaturation;
}

/**
 * 明度（Value）を取得する
 */
uint8_t ColorDetector::getValue() const {
    return mValue;
}

/**
 * 青色かどうか判定する
 */
bool ColorDetector::isBlue() const {
    // 青色のHSV範囲を定義
    const uint16_t blueHueMin = 220;
    const uint16_t blueHueMax = 260;
    const uint8_t blueSatMin = 60;
    const uint8_t blueValMin = 50;

    // printf("Hue: %d, Saturation: %d, Value: %d\n", mHue, mSaturation, mValue); // デバッグ用の出力

    return (mHue >= blueHueMin && mHue <= blueHueMax) &&
           (mSaturation >= blueSatMin) &&
           (mValue >= blueValMin);
}

bool ColorDetector::isBlack() const {
    // 黒色のHSV範囲を定義
    const uint8_t blackSatMax = 30;
    const uint8_t blackColorValMax = 30;

    return (mSaturation <= blackSatMax) &&
           (mValue <= blackColorValMax);
}

bool ColorDetector::isWhite() const {
    // 白色のHSV範囲を定義
    const uint8_t whiteSatMax = 30;
    const uint8_t whiteColorValMin = 70;

    return (mSaturation <= whiteSatMax) &&
           (mValue >= whiteColorValMin);
}