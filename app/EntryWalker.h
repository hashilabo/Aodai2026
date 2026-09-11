/**
 * EntryWalker.h
 */

#ifndef ETTR_APP_ENTRYWALKER_H_
#define ETTR_APP_ENTRYWALKER_H_

#include "Starter.h"
#include "SimpleTimer.h"

#include "LineTracer.h"
#include "ScenarioTracer.h"

class EntryWalker
{
public:
    EntryWalker(LineTracer *lineTracer,
                ScenarioTracer *scenarioTracer,
                const Starter *starter,
                SimpleTimer *simpleTimer);

    void run();

private:
    enum State
    {
        UNDEFINED,
        WAITING_FOR_START,
        LINE_TRACING,
        SCENARIO_TRACING,
        GARAGE,
        STOP
    };

    static const int MIN_TIME;
    static const int MAX_TIME;

    LineTracer *mLineTracer;
    ScenarioTracer *mScenarioTracer;
    const Starter *mStarter;
    SimpleTimer *mSimpleTimer;
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
