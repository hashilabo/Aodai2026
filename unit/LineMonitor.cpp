/******************************************************************************
 *  LineMonitor.cpp (for SPIKE)
 *  Created on: 2025/01/05
 *  Implementation of the Class LineMonitor
 *  Author: Kazuhiro.Kawachi
 *  Modifier: Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "LineMonitor.h"
#include  <cstdio>

// 定数宣言
const int8_t LineMonitor::INITIAL_THRESHOLD_BLACK = 10;  // 黒色の光センサ値
const int8_t LineMonitor::INITIAL_THRESHOLD_WHITE = 28;  // 白色の光センサ値

/**
 * コンストラクタ
 * @param colorSensor カラーセンサ
 * @param cutoffFreqHz LPFのカットオフ周波数(Hz)
 * @param sampleTimeSec LPFのサンプリング周期(秒)
 */
LineMonitor::LineMonitor(const spikeapi::ColorSensor& colorSensor, 
                         float cutoffFreqHz, float sampleTimeSec)
    : mColorSensor(colorSensor),
      mReflectionFilter(cutoffFreqHz, sampleTimeSec),
      mThreshold((INITIAL_THRESHOLD_BLACK + INITIAL_THRESHOLD_WHITE)/2),
      mFilteredReflection(0.0f) {
}

/**
 * ライン境界から外れた度合いを判定する
 * @retval ライン境界とセンサ値との差分
 */
int LineMonitor::calDiffReflection() {
    // 光センサからの取得値を見てローパスフィルタで平滑化し、
    // ライン境界の値との差分を算出して返す

    // mFilteredReflection = mReflectionFilter.update(mColorSensor.getReflection());
    update();  // 平滑化を行う
    int diff = (int)(mFilteredReflection - mThreshold);

    // printf("Filtered Reflection: %.2f, Threshold: %d, Diff: %d\n", mFilteredReflection, mThreshold, diff);
    return diff;
}

/**
 * ライン閾値を設定する
 * @param threshold ライン閾値
 */
void LineMonitor::setThreshold(int8_t threshold) {
    mThreshold = threshold;
}

/**
 * 反射率の平滑化を行う
 */
void LineMonitor::update() {
    // 光センサからの取得値を見て
    // 反射率の平滑化を行う
    mFilteredReflection = mReflectionFilter.update(mColorSensor.getReflection());
}

