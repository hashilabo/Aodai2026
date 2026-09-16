/**
 * EntryWalker.h
 */

#ifndef ETTR_APP_ENTRYWALKER_H_
#define ETTR_APP_ENTRYWALKER_H_

#include "Starter.h"
#include "SimpleTimer.h"
#include "OdoMeter.h"

#include "LineTracer.h"
#include "ScenarioTracer.h"

class EntryWalker
{
public:
    EntryWalker(LineTracer *lineTracer,
                ScenarioTracer *scenarioTracer,
                const Starter *starter,
                SimpleTimer *simpleTimer,
                OdoMeter *odoMeter);

    void run();

private:
    enum State
    {
        UNDEFINED,          // 未定義
        WAITING_FOR_START,  // スタート待機中
        LINE_TRACING,       // ライントレース中
        SCENARIO_TRACING,   // シナリオトレース中
        GARAGE,             // ガレージ走行中
        STOP                // 停止中
    };

    static const int MIN_TIME;
    static const int MAX_TIME;

    LineTracer *mLineTracer;
    ScenarioTracer *mScenarioTracer;
    const Starter *mStarter;
    SimpleTimer *mSimpleTimer;
    OdoMeter *mOdoMeter;
    State mState;

    int getRandomTime();
    void modeChangeAction();
    void execUndefined();
    void execWaitingForStart();
    void execLineTracing();
    void execScenarioTracing();
    void execGarage();
    void execStop();
};

#endif // ETTR_APP_ENTRYWALKER_H_
