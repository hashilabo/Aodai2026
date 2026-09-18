/******************************************************************************
 *  ScenarioTracer.cpp (for SPIKE)
 *  Created on: 2025/01/05
 *  Implementation of the Class ScenarioTracer
 *  Author: Kenya Yabe
 *  Modifier: Yuki Tsuchitoi
 *  Copyright (c) 2025 Embedded Technology Software Design Robot Contest
 *****************************************************************************/

#include "ScenarioTracer.h"
#include "LineTracer.h"
#include "etroboc_ext.h"

// 定数定義
const int ScenarioTracer::DEFAULT_PWM = 25;
const int ScenarioTracer::DEFAULT_TURN = 25;
const int ScenarioTracer::DEFAULT_BIAS = 0;

/**
 * コンストラクタ
 * @param walker          走行
 * @param scenario        シナリオ
 * @param timer           タイマ
 */
ScenarioTracer::ScenarioTracer(Walker* walker,
                               Scenario* scenario,
                               SimpleTimer* timer)
    : mWalker(walker),
      mScenario(scenario),
      mSimpleTimer(timer),
      mState(UNDEFINED) {
}

/**
 * シナリオトレースする
 */
void ScenarioTracer::run() {
    switch (mState) {
    case UNDEFINED:
        execUndefined();
        break;
    case INITIAL:
        execInitial();
        break;
    case WALKING:
        execWalking();
        break;
    default:
        break;
    }
}

/**
 * シナリオトレース初期化処理
 */
void ScenarioTracer::initAction() {
    mWalker->init();
}

/**
 * トレースコマンド設定
 * @param command 走行向き
 */
void ScenarioTracer::setCommand(SceneCommands command) {
    int pwm = 0;
    int turn = -1;
    int bias = 0;

    switch (command)
    {
    case SceneCommands::GO_STRAIGHT:   // 直進の場合
        pwm  = DEFAULT_PWM;
        turn = 0;
        bias = DEFAULT_BIAS;
        break;
    case SceneCommands::TURN_LEFT:     // 左前ターン
        pwm  = DEFAULT_PWM;
        turn = DEFAULT_TURN * (-LineTracer::_EDGE);
        bias = DEFAULT_BIAS;
        break;
    case SceneCommands::TURN_RIGHT:    // 右前ターン
        pwm  = DEFAULT_PWM;
        turn = - DEFAULT_TURN * (-LineTracer::_EDGE);
        bias = DEFAULT_BIAS;
        break;
    case SceneCommands::BACKWARD:      // 後退
        pwm  = - DEFAULT_PWM;
        turn = 0;
        bias = DEFAULT_BIAS;
        break;
    case SceneCommands::TURN_BACK_LEFT: // 左後ターン
        pwm  = - DEFAULT_PWM;
        turn = DEFAULT_TURN * (-LineTracer::_EDGE);
        bias = DEFAULT_BIAS;
        break;
    case SceneCommands::TURN_BACK_RIGHT:    // 右後ターン
        pwm  = - DEFAULT_PWM;
        turn = - DEFAULT_TURN * (-LineTracer::_EDGE);
        bias = DEFAULT_BIAS;
        break;
    case SceneCommands::STOP:           // 停止
        pwm  = 0;
        turn = 0;
        bias = 0;
        break;
    case SceneCommands::FINISH:         // 完全停止
        pwm  = 0;
        turn = 0;
        bias = 0;
        ETRoboc_notifyCompletedToSimulator();
        break;
    default:
        break;
    }

    // if (command == TURN_LEFT) {
    //   turn = Walker::LEFT_TURN;
    // } else if (command == TURN_RIGHT) {
    //   turn = Walker::RIGHT_TURN;
    // }

    // mWalker->setCommand(turn);
    mWalker->setCommand(pwm, turn, bias);
}

/**
 * シーン変更処理
 */
void ScenarioTracer::modeChangeAction() {
    mScenario->next();

    SceneCommands command = mScenario->currentSceneCommand();
    setCommand(command);

    mSimpleTimer->setTime(mScenario->currentSceneTime());
    mSimpleTimer->start();
}

/**
 * 未定義状態の処理
 */
void ScenarioTracer::execUndefined() {
    mState = INITIAL;
}

/**
 * 初期状態の処理
 */
void ScenarioTracer::execInitial() {
    initAction();   		// ① entry アクション(INITIAL)

    mState = WALKING;   	// ① 状態遷移

    modeChangeAction();     // ① entry アクション(WALKING)
}

/**
 * 走行中状態の処理
 */
void ScenarioTracer::execWalking() {
    mWalker->run();             		// ② do アクティビティ

    if (mSimpleTimer->isTimedOut()) {   // ② イベントチェック
        mSimpleTimer->stop();   		// ② exit アクション

        modeChangeAction();     		// ② entry アクション(WALKING)
    }
}
