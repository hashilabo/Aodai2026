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
                float cutoffFreqHz, float sampleTimeSec);

    int calDiffReflection();
    void setThreshold(int8_t threshold);

private:
    static const int8_t INITIAL_THRESHOLD_BLACK;
	static const int8_t INITIAL_THRESHOLD_WHITE;

    const spikeapi::ColorSensor& mColorSensor;
    LowPassFilter mLowPassFilter;
    float mFilteredReflection;
    int8_t mThreshold;

};

#endif  // ETTR_UNIT_LINEMONITOR_H_
