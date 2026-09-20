/******************************************************************************
 *  LineMonitor.h (for SPIKE )
 *  Created on: 2025/01/05
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Modifier : Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef ETTR_UNIT_LINEMONITOR_H_
#define ETTR_UNIT_LINEMONITOR_H_

#include "ColorSensor.h"
#include "LowPassFilter.h"

// 定義
class LineMonitor {
public:
    LineMonitor(const spikeapi::ColorSensor& colorSensor, 
                float cutoffFreqHz = 25.0f, float sampleTimeSec = 0.01f);

    int calDiffReflection();
    void setThreshold(int8_t threshold);
    void update();

private:
    static const int8_t INITIAL_THRESHOLD_BLACK;
	static const int8_t INITIAL_THRESHOLD_WHITE;

    const spikeapi::ColorSensor& mColorSensor;  // カラーセンサの参照
    LowPassFilter mReflectionFilter;            // LPFによる反射率の平滑化
    int8_t mThreshold;                          // ライン閾値
    float mFilteredReflection;                  // 平滑化された反射率
};

#endif  // ETTR_UNIT_LINEMONITOR_H_
