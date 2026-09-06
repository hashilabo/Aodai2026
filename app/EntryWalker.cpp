/**
 * EntryWalker.cpp
 */

#include <stdlib.h>
#include "Clock.h"

#include "EntryWalker.h"
#include "etroboc_ext.h"

// 定数宣言
const int EntryWalker::MIN_TIME = 60000 * 1000;  // 切り替え時間の最小値
const int EntryWalker::MAX_TIME = 120000 * 1000; // 切り替え時間の最大値

/**
 * コンストラクタ
 * @param lineTracer      ライントレーサ
 * @param scenarioTracer  シナリオトレーサ
 * @param starter         スタータ
 * @param simpleTimer     タイマ
 */
EntryWalker::EntryWalker(LineTracer *lineTracer,
                         ScenarioTracer *scenarioTracer,
                         const Starter *starter,
                         SimpleTimer *simpleTimer)
    : mLineTracer(lineTracer),
      mScenarioTracer(scenarioTracer),
      mStarter(starter),
      mSimpleTimer(simpleTimer),
      mState(UNDEFINED)
{
    spikeapi::Clock *clock = new spikeapi::Clock();

    srand(clock->now()); // 乱数をリセットする

    delete clock;
}

/**
 * ランダム走行する
 */
void EntryWalker::run()
{
    switch (mState)
    {
    case UNDEFINED:
        execUndefined();
        break;
    case WAITING_FOR_START:
        execWaitingForStart();
        break;
    case LINE_TRACING:
        execLineTracing();
        break;
    case SCENARIO_TRACING:
        execScenarioTracing();
        break;
    default:
        break;
    }
}

/**
 * 乱数を取得する
 * @retrun 乱数
 */
int EntryWalker::getRandomTime()
{
    return MIN_TIME +
           static_cast<int>(static_cast<double>(rand()) *
                            (MAX_TIME - MIN_TIME + 1.0) / (1.0 + RAND_MAX));
}

/**
 * シーン変更処理
 */
void EntryWalker::modeChangeAction()
{
    mSimpleTimer->setTime(getRandomTime());
    mSimpleTimer->start();
}

/**
 * 未定義状態の処理
 */
void EntryWalker::execUndefined()
{
    mState = WAITING_FOR_START;
}

/**
 * 開始待ち状態の処理
 */
void EntryWalker::execWaitingForStart()
{
    if (mStarter->isPushed())
    {
        mState = LINE_TRACING;

        modeChangeAction();
    }
}

/**
 * ライントレース状態の処理
 */
void EntryWalker::execLineTracing()
{
    mLineTracer->run();

    if (mSimpleTimer->isTimedOut())
    {
        mSimpleTimer->stop();

        mState = STOP;

        modeChangeAction();
    }
}

/**
 * シナリオトレース状態の処理
 */
void EntryWalker::execScenarioTracing()
{
    mScenarioTracer->run();

    if (mSimpleTimer->isTimedOut())
    {
        mSimpleTimer->stop();

        mState = STOP;

        modeChangeAction();
    }
}

void EntryWalker::execStop()
{
    ETRoboc_notifyCompletedToSimulator(); // 競技終了通知
}