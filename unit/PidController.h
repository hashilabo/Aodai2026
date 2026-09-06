/**
 * PidController.h
 */

#ifndef ETTR_APP_PIDCONTROLLER_H_
#define ETTR_APP_PIDCONTROLLER_H_

class PidController
{
public:
    // pid.txt が存在しない場合に使うデフォルト値
    static const float DEFAULT_Kp;           // 比例ゲイン
    static const float DEFAULT_Ki;           // 積分ゲイン
    static const float DEFAULT_Kd;           // 微分ゲイン
    static const float DEFAULT_BIAS;         // バイアス
    static const float PERIOD_SEC;           // 周期ハンドラの周期[s]
    static const char *const PID_PARAM_FILE; // PIDパラメータ設定ファイル名

    // コンストラクタ
    PidController();

    // 積分項や前回偏差などの内部状態をリセットする
    void reset();

    // 偏差からPID制御量を計算する
    float calcValue(int diffReflection);

private:
    float mKp;   // 比例ゲイン
    float mKi;   // 積分ゲイン
    float mKd;   // 微分ゲイン
    float mBias; // バイアス

    float mIntegral;         // 積分項の値
    int mPrevDiffReflection; // 前回の偏差値

    void loadPidParams(); // PIDパラメータをファイルから読み込む
};

#endif // ETTR_APP_PIDCONTROLLER_H_