/******************************************************************************
 *  PidController.h (for SPIKE)
 *  Created on: 2026/08/07
 *  Definition of the Class PidController
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#ifndef ETTR_APP_PIDCONTROLLER_H_
#define ETTR_APP_PIDCONTROLLER_H_

class PidController {
public:
	// pid.txt が存在しない場合に使うデフォルト値
	static const float DEFAULT_Kp;
	static const float DEFAULT_Ki;
	static const float DEFAULT_Kd;
	static const float DEFAULT_BIAS;
	static const float PERIOD_SEC;  // 周期ハンドラの周期[s]
	static const char* const PID_PARAM_FILE;  // PIDパラメータ設定ファイル名

	PidController();

	// 積分項や前回偏差などの内部状態をリセットする
	void reset();

	// 偏差からPID制御量を計算する
	float calcValue(int diffReflection);

private:
    float mKp;
    float mKi;
    float mKd;
    float mBias;

    float mIntegral;
    int mPrevDiffReflection;

    void loadPidParams();
};

#endif  // ETTR_APP_PIDCONTROLLER_H_
