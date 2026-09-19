/******************************************************************************
 *  LineMonitor.cpp (for SPIKE)
 *  Created on: 2025/01/05
 *  Implementation of the Class LineMonitor
 *  Author: Kazuhiro.Kawachi
 *  Modifier: Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineMonitor.h"
#include <cstdio>


// 定数宣言
const int8_t LineMonitor::INITIAL_THRESHOLD_BLACK =  6;  // 黒色の光センサ値
const int8_t LineMonitor::INITIAL_THRESHOLD_WHITE = 40;  // 白色の光センサ値

/**
 * コンストラクタ
 * @param colorSensor カラーセンサ
 */
LineMonitor::LineMonitor(const spikeapi::ColorSensor& colorSensor,
                         float cutoffFreqHz, float sampleTimeSec)
    : mColorSensor(colorSensor),
      mLowPassFilter(cutoffFreqHz, sampleTimeSec),
      mFilteredReflection(0.0f),
      mThreshold((INITIAL_THRESHOLD_BLACK + INITIAL_THRESHOLD_WHITE)/2) 
      {}

/**
 * ライン境界から外れた度合いを判定する
 * @retval ライン境界とセンサ値との差分
 */
int LineMonitor::calDiffReflection() {
    // 光センサからの取得値を見て
    // ライン境界の値との差分を算出して返す
    // int diff = mColorSensor.getReflection() - (int)mThreshold;

    int reflection = mColorSensor.getReflection();
    mFilteredReflection = mLowPassFilter.update((float)reflection);

    int diff = (int)(mFilteredReflection - (float)mThreshold);

    printf("Reflection: %d, Filtered: %.2f, Threshold: %d, Diff: %d\n",
           reflection, mFilteredReflection, mThreshold, diff); // デバッグ用の出力

    return diff;
}

/**
 * ライン閾値を設定する
 * @param threshold ライン閾値
 */
void LineMonitor::setThreshold(int8_t threshold) {
    mThreshold = threshold;
}
