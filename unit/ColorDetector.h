/**
 * ColorDetector.h
 */
#ifndef ETTR_UNIT_COLORDETECTOR_H_
#define ETTR_UNIT_COLORDETECTOR_H_

#include "ColorSensor.h"

class ColorDetector {
 public:
    explicit ColorDetector(const spikeapi::ColorSensor& colorSensor);

    void update();          // HSV色情報を更新する
    bool isBlue() const;    // 青色かどうか判定する 
    bool isBlack() const;   // 黒色かどうか判定する
    bool isWhite() const;   // 白色かどうか判定する

 private:
    uint16_t mHue;          // 色相（Hue）
    uint8_t mSaturation;    // 彩度（Saturation）
    uint8_t mValue;         // 明度（Value）

    const spikeapi::ColorSensor& mColorSensor;  // 関連端名: ColorSensorの参照

    uint16_t getHue() const;        // 色相（Hue）を取得する
    uint8_t getSaturation() const;  // 彩度（Saturation）を取得する
    uint8_t getValue() const;       // 明度（Value）を取得する
};

#endif  // ETTR_UNIT_COLORDETECTOR_H_