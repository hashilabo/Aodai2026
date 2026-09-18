/******************************************************************************
 *  Walker.cpp (for SPIKE)
 *  Created on: 2025/01/05
 *  Implementation of the Class Walker
 *  Author: Kazuhiro.Kawachi
 *  Modifier: Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "Walker.h"

/**
 * コンストラクタ
 * @param leftWheel  左モータ
 * @param rightWheel 右モータ
 */
Walker::Walker(spikeapi::Motor& leftWheel,
                                 spikeapi::Motor& rightWheel)
    : mLeftWheel(leftWheel),
      mRightWheel(rightWheel),
      mPwm(0),
      mTurn(0),
      mBias(0) {
}

/**
 * 走行する
 */
void Walker::run() {
    // 左右モータに回転を指示する   
	mLeftWheel.setPower(mPwm - mTurn - mBias); 
	mRightWheel.setPower(mPwm + mTurn + mBias);
	
}

/**
 * 走行に必要なものをリセットする
 */
void Walker::init() {
    // モータをリセットする
    mLeftWheel.resetCount();
    mRightWheel.resetCount();
}

/**
 * PWM値を設定する
 * @param forward 前進値
 * @param turn    旋回方向
 */
void Walker::setCommand(float turn) {
    mTurn    = turn;
}

/**
 * pwm, turn, bias を設定する
 * @param pwm 前進量
 * @param turn 旋回量
 * @param bias バイアス
 */
void Walker::setCommand(float pwm, float turn, float bias) {
    mPwm = pwm,
    mTurn = turn;
    mBias = bias;
}
