/**
 * PidController.cpp
 */

#include "PidController.h"
#include <cstdio>
#include <cstring>

// 定数宣言
const float PidController::DEFAULT_Kp = 2.83;
const float PidController::DEFAULT_Ki = 0.05;
const float PidController::DEFAULT_Kd = 2.50;
const float PidController::DEFAULT_BIAS = 0;
// CYC_TRACER(app.cfg)の周期と合わせること
const float PidController::PERIOD_SEC = 0.01;
// 実行時のカレントディレクトリ（workspaceディレクトリ）に置く
const char *const PidController::PID_PARAM_FILE = "pid.txt";

/**
 * コンストラクタ
 */
PidController::PidController()
    : mKp(PidController::DEFAULT_Kp),
      mKi(PidController::DEFAULT_Ki),
      mKd(PidController::DEFAULT_Kd),
      mBias(PidController::DEFAULT_BIAS),
      mIntegral(0.0f),
      mPrevDiffReflection(0)
{
    loadPidParams();
}

/**
 * PIDパラメータを外部ファイル（pid.txt）から読み込む
 * ファイルが無い、または項目が無い場合はデフォルト値のまま
 * ファイル書式（1行に1項目）:
 *   Kp=0.83
 *   Ki=0.02
 *   Kd=0.05
 *   bias=0
 */
void PidController::loadPidParams()
{
    FILE *fp = fopen(PidController::PID_PARAM_FILE, "r");
    if (fp == NULL)
    {
        printf("%s not found. use default PID parameters.\n",
               PidController::PID_PARAM_FILE);
        return;
    }

    char line[64];
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char key[16];
        float value;
        if (sscanf(line, "%15[^=]=%f", key, &value) == 2)
        {
            if (strcmp(key, "Kp") == 0)
            {
                mKp = value;
            }
            else if (strcmp(key, "Ki") == 0)
            {
                mKi = value;
            }
            else if (strcmp(key, "Kd") == 0)
            {
                mKd = value;
            }
            else if (strcmp(key, "bias") == 0)
            {
                mBias = value;
            }
        }
    }
    fclose(fp);

    printf("PID parameters loaded from %s: Kp=%f Ki=%f Kd=%f bias=%f\n",
           PidController::PID_PARAM_FILE, mKp, mKi, mKd, mBias);
}

/**
 * 積分項や前回偏差などの内部状態をリセットする
 */
void PidController::reset()
{
    mIntegral = 0.0f;
    mPrevDiffReflection = 0;
}

/**
 * 偏差からPID制御量を計算する
 * @param diffReflection ラインから外れた度合い（ライン閾値との差）
 */
float PidController::calcValue(int diffReflection)
{
    // P項
    float pTerm = mKp * diffReflection;

    // I項（誤差の積分）
    mIntegral += diffReflection * PidController::PERIOD_SEC;
    float iTerm = mKi * mIntegral;

    // D項（誤差の変化率）
    float derivative = (diffReflection - mPrevDiffReflection) / PidController::PERIOD_SEC;
    float dTerm = mKd * derivative;

    mPrevDiffReflection = diffReflection;

    float turn = pTerm + iTerm + dTerm + mBias;

    return turn;
}