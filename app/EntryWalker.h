/******************************************************************************
 * EntryWalker.h
 *****************************************************************************/

#ifndef ETTR_APP_ENTRYWALKER_H_
#define ETTR_APP_ENTRYWALKER_H_

#include "Starter.h"
#include "SimpleTimer.h"
#include "ColorDetector.h"

#include "LineTracer.h"
#include "ScenarioTracer.h"

class EntryWalker {
public:
    EntryWalker(LineTracer* lineTracer,
                ScenarioTracer* scenarioTracer,
                 const Starter* starter,
                 SimpleTimer* simpleTimer,
                 ColorDetector* colorDetector);

    void run();

private:
    enum State {
        UNDEFINED,              // 初期化前
        WAITING_FOR_START,      // スタート待機中
        LINE_TRACING,           // ライントレース中
        SCENARIO_TRACING,       // シナリオトレース中
        GARAGE,                 // ガレージ中
        STOP                    // 停止中
    };

    static const int MIN_TIME;
    static const int MAX_TIME;

    LineTracer* mLineTracer;
    ScenarioTracer* mScenarioTracer;
    const Starter* mStarter;
    SimpleTimer* mSimpleTimer;
    ColorDetector* mColorDetector;
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

#endif  // ETTR_APP_ENTRYWALKER_H_
